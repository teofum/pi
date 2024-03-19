#!/bin/bash

cmd=${4:-gcc} # Use clang (aliased) on mac
#cmd=${4:-$CC} # Use gcc on mac (needs envvar set in .zshrc)

src=./$1/$1_$2.c
args="$3 -I ./lib -std=c99 -pedantic -Wall -lm -o out/$1_$2"

# Auto-detect use of my_getnum lib and add it to compile command
cat $src | grep my_getnum > /dev/null
if [[ $? ]]; then
  $cmd $src lib/my_getnum.c $args
else
  $cmd $src $args
fi

# Run the output executable
./out/$1_$2