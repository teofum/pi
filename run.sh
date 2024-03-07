#!/bin/bash

$CC ./$1/$1_$2.c $3 -o out/$1_$2
./out/$1_$2