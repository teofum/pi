#!/bin/bash

exclude_dirs=(".vscode" "cmake-build-debug" "cmake-build-docker" "lib" "out")

echo "# Auto generated CMakeLists.txt" > CMakeLists.txt

while read line; do
  echo $line >> CMakeLists.txt
done < CMakeLists.template.txt

for dir in */; do
  dir=${dir%*/}

  # Iterate each directory not in exclude_dirs
  if [[ ! " ${exclude_dirs[*]} " =~ [[:space:]]${dir}[[:space:]] ]]; then
    echo "" >> CMakeLists.txt
    echo "# $dir/" >> CMakeLists.txt

    for file in $dir/*.c; do
      # Auto-detect use of libs and add it to compile command
      out=$(basename -- "$file")
      out=${out%.*}
      src=$file
      for lib in lib/*.h; do
        lib_name=$(echo $lib | sed -E 's#lib/([a-zA-Z0-9_]+)\.h#\1#')
        cat $src | grep "$lib_name.h" > /dev/null
        if [[ $? = 0 ]]; then
          src="$src lib/$lib_name.c"
        fi
      done

      echo "add_executable($out $src)" >> CMakeLists.txt
    done
  fi
done

