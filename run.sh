#!/bin/bash

cmd=${4:-gcc} # Use clang (aliased) on mac
#cmd=${4:-$CC} # Use gcc on mac

src=./$1/$1_$2.c

# Auto-detect use of my_getnum lib and add it to compile command
cat $src | grep my_getnum > /dev/null
if [[ $? ]]; then
  $cmd $src lib/my_getnum.c $3 -std=c99 -pedantic -Wall -o out/$1_$2
else
  $cmd $src $3 -std=c99 -pedantic -Wall -o out/$1_$2
fi

# Run the output executable
./out/$1_$2