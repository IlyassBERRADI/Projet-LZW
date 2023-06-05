#ifndef __STR_H__
#define __STR_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _str {
    char* data;
    int size;
    int max_size;
} *Str;

Str str_create(char* str, int size, int max_size);

Str str_create_empty(int max_size);

Str str_copy(Str str, int max_size);

int str_equals(Str s1, Str s2);

void str_append(Str str, char c);

void str_free(Str str);

void str_empty(Str str);

void str_write(FILE* file, Str str);

#endif