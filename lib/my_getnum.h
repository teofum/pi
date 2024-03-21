#ifndef _getnum_h
#define _getnum_h

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int get_int(const char prompt[], ...);
long get_long(const char prompt[], ...);
float get_float(const char prompt[], ...);
double get_double(const char prompt[], ...);
int get_yes_no(const char prompt[], ...);

#endif
