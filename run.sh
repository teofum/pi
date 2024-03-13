#!/bin/bash

cmd=${4:-gcc} # Use clang (aliased) on mac
#cmd=${4:-$CC} # Use gcc on mac

$cmd ./$1/$1_$2.c $3 -std=c99 -pedantic -Wall -o out/$1_$2
./out/$1_$2