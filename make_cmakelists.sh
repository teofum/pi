#!/bin/bash

exclude_dirs=(".vscode" "cmake-build-debug" "cmake-build-docker" "lib" "adt" "out")

echo "# Auto generated CMakeLists.txt" > CMakeLists.txt

while read line; do
  echo $line >> CMakeLists.txt
done < CMakeLists.template.txt

echo "" >> CMakeLists.txt
echo "# Libraries" >> CMakeLists.txt
for file in lib/*.c; do
  # Auto-detect use of libs and add it to compile command
  out=$(basename -- "$file")
  out=${out%.*}

  echo "add_library($out $file)" >> CMakeLists.txt
  echo "lib $out"

  for lib in lib/*.h; do
    lib_name=$(basename -- "$lib")
    lib_name=${lib_name%.*}
    cat $file | grep "$lib_name.h" > /dev/null
    if [[ $? = 0  ]] && [[ $lib_name != $out ]]; then
      echo "target_link_libraries($out $lib_name)" >> CMakeLists.txt
    fi
  done
done

echo "" >> CMakeLists.txt
echo "# ADT" >> CMakeLists.txt
for file in adt/*.c; do
  # Auto-detect use of libs and add it to compile command
  out=$(basename -- "$file")
  out=${out%.*}

  echo "add_library($out $file)" >> CMakeLists.txt
  echo "adt $out"

  for lib in lib/*.h; do
    lib_name=$(basename -- "$lib")
    lib_name=${lib_name%.*}
    cat $file | grep "$lib_name.h" > /dev/null
    if [[ $? = 0  ]] && [[ $lib_name != $out ]]; then
      echo "target_link_libraries($out $lib_name)" >> CMakeLists.txt
    fi
  done
done

echo "" >> CMakeLists.txt
echo "# Executables" >> CMakeLists.txt
for dir in */; do
  dir=${dir%*/}

  # Iterate each directory not in exclude_dirs
  if [[ ! " ${exclude_dirs[*]} " =~ [[:space:]]${dir}[[:space:]] ]]; then
    for file in $dir/*.c; do
      out=$(basename -- "$file")
      out=${out%.*}

      echo "add_executable($out $file)" >> CMakeLists.txt
      echo "target $out"

      # Auto-detect use of libs
      for lib in lib/*.h; do
        lib_name=$(basename -- "$lib")
        lib_name=${lib_name%.*}
        cat $file | grep "$lib_name.h" > /dev/null
        if [[ $? = 0  ]]; then
          echo "target_link_libraries($out $lib_name)" >> CMakeLists.txt
        fi
      done

      # Auto-detect use of ADT libs
      for adt in adt/*.h; do
        adt_name=$(basename -- "$adt")
        adt_name=${adt_name%.*}
        cat $file | grep "$adt_name.h" > /dev/null
        if [[ $? = 0  ]]; then
          echo "target_link_libraries($out $lib_name)" >> CMakeLists.txt
        fi
      done
    done
  fi
done

