#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocate and create a copy of str.
 * 
 * @param str String to copy.
 * @param size Number of element to copy.
 * @param max_size Number of element to allocate.
 */
char* str_duplicate(char* str, int size, int max_size) {
    /* Allocate memory */
    char* dest = malloc(sizeof(char) * max_size);

    /* Copy data */
    int i;
    for (i = 0; i < size; i++) {
        dest[i] = str[i];
    }

    return dest;
}

Str str_create(char* str, int size, int max_size) {
    Str new = malloc(sizeof(struct _str));
    new->data = str_duplicate(str, size, max_size);
    new->size = size;
    new->max_size = max_size;
    return new;
}

Str str_create_empty(int max_size) {
    return str_create("", 0, max_size);
}

Str str_copy(Str str, int max_size) {
    return str_create(str->data, str->size, max_size);
}

int str_equals(Str s1, Str s2) {
    /* Compare size */
    if (s1->size != s2->size) return 0;
    int i;
    /* Compare data */
    for (i = 0; i < s1->size; i++) {
        if (s1->data[i] != s2->data[i]) return 0;
    }
    return 1;
}

void str_append(Str str, char c) {
    if (str->size == str->max_size) {
        printf("Can't append char : the string is already full.\n");
        exit(1);
    }
    str->data[str->size] = c;
    str->size++;
}

void str_empty(Str str) {
    str->size = 0;
}

void str_free(Str str) {
    free(str->data);
    free(str);
}

void str_write(FILE* file, Str str) {
    int i;
    for (i = 0; i < str->size; i++) {
        fputc(str->data[i], file);
    }
}
