#!/bin/bash

cmd=${4:-gcc} # Use clang (aliased) on mac
#cmd=${4:-$CC} # Use gcc on mac (needs envvar set in .zshrc)

src=./$1/$1_$2.c
args="$3 -I ./lib -std=c99 -pedantic -Wall -lm -o out/$1_$2"

# Auto-detect use of libs and add it to compile command
cat $src | grep my_getnum > /dev/null
if [[ $? ]]; then
  src="$src lib/my_getnum.c"
fi

cat $src | grep random > /dev/null
if [[ $? ]]; then
  src="$src lib/random.c"
fi

# Compile
$cmd $src $args

# Run the output executable
./out/$1_$2