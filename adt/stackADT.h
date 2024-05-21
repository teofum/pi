#ifndef _stackADT_h
#define _stackADT_h

#include <stddef.h>

typedef struct stackCDT *stackADT;

stackADT new_stack(void);

void free_stack(stackADT stack);

int is_empty(const stackADT stack);

size_t size(const stackADT stack);

void push(stackADT stack, int elem);

int pop(stackADT stack);

int peek(const stackADT stack);

#endif
