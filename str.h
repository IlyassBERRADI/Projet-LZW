#ifndef __STR_H__
#define __STR_H__

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Data which can contains \0.
 */
typedef struct _str {
    /** @brief Contains all characters. */
    char* data;
    /** @brief Current size of the data. */
    int size;
    /** @brief The max size of the data. */
    int max_size;
} *Str;

/**
 * @brief Create a new empty Str.
 * @param max_size The max size of data.
 */
Str str_create(int max_size);

/**
 * @brief Create a copy of an str with a new max_size.
 */
Str str_copy(Str str, int max_size);

/**
 * @brief Return 1 if s1 and s2 are equals.
 * Do not compare max_size.
 */
int str_equals(Str s1, Str s2);

/**
 * @brief Add a single character at the add of data.
 */
void str_append(Str str, char c);

/**
 * @brief Liberate memory allocated to str.
 */
void str_free(Str str);

/**
 * @brief Empty the data of str.
 */
void str_empty(Str str);

/**
 * @brief Write the content of str inside a file.
 */
void str_write(FILE* file, Str str);

#endif