#!/bin/bash

cmd=${4:-$CC}

$cmd ./$1/$1_$2.c $3 -o out/$1_$2
./out/$1_$2