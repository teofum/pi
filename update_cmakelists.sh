#!/bin/bash

# Remove executable line if it exists
sed "/^add_executable($2/d" CMakeLists.txt > temp
mv temp CMakeLists.txt

# Auto-detect use of libs and add it to compile command
src=$1
for lib in lib/*.h; do
  lib_name=$(echo $lib | sed -E 's#lib/([a-zA-Z0-9_]+)\.h#\1#')
  cat $src | grep "$lib_name.h" > /dev/null
  if [[ $? = 0 ]]; then
    src="$src lib/$lib_name.c"
  fi
done

echo "add_executable($2 $src)" >> CMakeLists.txt