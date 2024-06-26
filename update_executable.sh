#!/bin/bash

if [[ $1 == *c ]]; then
  # Remove executable line if it exists
  sed "/^add_executable($2/d" CMakeLists.txt > temp
  sed "/^target_link_libraries($2/d" temp > CMakeLists.txt
  rm temp

  echo "add_executable($2 $1)" >> CMakeLists.txt

  # Auto-detect use of libs
  for lib in lib/*.h; do
    lib_name=$(basename -- "$lib")
    lib_name=${lib_name%.*}
    cat $1 | grep "$lib_name.h" > /dev/null
    if [[ $? = 0  ]]; then
      echo "target_link_libraries($2 $lib_name)" >> CMakeLists.txt
    fi
  done

  # Auto-detect use of ADT libs
  for adt in adt/*.h; do
    adt_name=$(basename -- "$adt")
    adt_name=${adt_name%.*}
    cat $1 | grep "$adt_name.h" > /dev/null
    if [[ $? = 0  ]]; then
      echo "target_link_libraries($2 $adt_name)" >> CMakeLists.txt
    fi
  done
fi