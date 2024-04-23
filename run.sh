#!/bin/bash

cmd=${4:-gcc} # Use clang (aliased) on mac
#cmd=${4:-$CC} # Use gcc on mac (needs envvar set in .zshrc)

src=./$1/$1_$2.c
args="-I ./lib -std=c99 -pedantic -Wall -lm -o out/$1_$2"

if [[ $3 == "san" ]]; then
  args="$args -fsanitize=address -g"
else
  args="$args $3"
fi

# Auto-detect use of libs and add it to compile command
for lib in lib/*.h; do
  lib_name=$(echo $lib | sed -E 's#lib/([a-zA-Z0-9_]+)\.h#\1#')
  cat $src | grep "$lib_name.h" > /dev/null
  if [[ $? = 0 ]]; then
    src="$src lib/$lib_name.c"
  fi
done

# Compile
$cmd $src $args

# Run the output executable
./out/$1_$2