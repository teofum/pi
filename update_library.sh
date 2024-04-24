#!/bin/bash

if [[ $1 == *c ]]; then
  # Remove library line if it exists
  sed "/^add_library($2/d" CMakeLists.txt > temp
  sed "/^target_link_libraries($2/d" temp > CMakeLists.txt
  rm temp

  echo "add_library($2 $1)" >> CMakeLists.txt

  # Auto-detect use of libs
  for lib in lib/*.h; do
    lib_name=$(basename -- "$lib")
    lib_name=${lib_name%.*}
    cat $1 | grep "$lib_name.h" > /dev/null
    if [[ $? = 0  ]] && [[ $lib_name != $2 ]]; then
      echo "target_link_libraries($2 $lib_name)" >> CMakeLists.txt
    fi
  done
fi
