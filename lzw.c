#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "mapen.h"
#include "mapde.h"

#define STR_SIZE 1024

void encode(FILE* src, FILE* dest) {
    /* Init */
    Map map = mapen_create();
    char c;
    char str[STR_SIZE] = { '\0' };
    int size = 0;
    uint32_t code;
    fprintf(dest, "%u ", CLEAR_CODE);

    /* Read file */
    while (!feof(src)) {
        if (mapen_get_code(map, str, &code)) {
            /* Continue reading file */
            c = fgetc(src);
            /* Add char to string */
            str[size++] = c;
            str[size] = '\0';
        } else {
            /* The current str has no code,
            write of previous valid code and creation of a new code */
            fprintf(dest, "%u ", code);
            mapen_add_str(map, str);
            /* str is now equals to the last character read */
            str[0] = str[size-1];
            str[1] = '\0';
            size = 1;
        }
    }

    /* Write last string */
    mapen_get_code(map, str, &code);
    if (size > 0) fprintf(dest, "%u ", code);
    /* Close the data */
    fprintf(dest, "%u", END_CODE);
    map_free(map);
}

/**
 * @brief Manage an array of two pointer to free.
 */
void update_trash(char* trash[], char* str) {
    if (trash[0] != NULL) free(trash[0]);
    trash[0] = trash[1];
    trash[1] = str;
}

/**
 * @brief Add to map a new string with last_str and new_char
 */
void add_to_map(Map map, char* last_str, char new_char) {
    static char to_add[1024] = { '\0' };

    int size = strlen(last_str);
    strcpy(to_add, last_str);
    to_add[size] = new_char;
    to_add[size+1] = '\0';
    mapde_add_str(map, to_add);
}

char* get_unknown_code(char* last_str) {
    int size = strlen(last_str) + 2;
    char* str = malloc(sizeof(char) * size);
    strcpy(str, last_str);
    str[size-2] = last_str[0];
    str[size-1] = '\0';
    return str;
}

void decode(FILE* src, FILE* dest) {
    Map map;
    uint32_t code = 0;
    char* last_str = NULL;
    char* str = NULL;
    char* trash[2] = { NULL };
    int i;

    while (1) {
        fscanf(src, "%u", &code);

        if (code == CLEAR_CODE) {
            /* Create a new map with only default code */
            map = mapde_create();
            continue;
        }

        /* End of file reached*/
        if (code == END_CODE) break;

        last_str = str;
        str = mapde_get_str(map, code);
        if (str == NULL) {
            /* No existing code */
            str = get_unknown_code(last_str);
            update_trash(trash, str);
        }

        fprintf(dest, "%s", str);

        /* Add a new code */
        if (last_str == NULL) continue;
        add_to_map(map, last_str, str[0]);
    }
    map_free(map);
    for (i = 0; i < 2; i++) {
        if (trash[i] != NULL) free(trash[i]);
    }
}

int main(int argc, char const *argv[]) {
    /* Check arguments count */
    if (argc < 4) {
        printf("You must enter 3 parameters to execute the program :\n");
        printf("- \"-e\" to encode or \"-d\" to decode a file;\n");
        printf("- The path of the target file to encode/decode;\n");
        printf("- The path of the generated file after encoding/decoding.\n");
        return 1;
    }

    /* Check path target */
    FILE* src = fopen(argv[2], "r");
    if (src == NULL) {
        printf("The target file does not exist.\n");
        return 1;
    }

    FILE* dest = fopen(argv[3], "w");

    if (strcmp("-e", argv[1]) == 0) {
        /* Encode file */
        encode(src, dest);
        printf("Encoding finished successfully.\n");
    } else if (strcmp("-d", argv[1]) == 0) {
        /* Decode file */
        decode(src, dest);
        printf("Decoding finished successfully.\n");
    } else {
        printf("First argument must be either \"-e\" or \"-d\".\n");
        fclose(src);
        fclose(dest);
        return 1;
    }

    fclose(src);
    fclose(dest);

    return 0;
}
