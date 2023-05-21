#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "mapen.h"
#include "mapde.h"

void encode(FILE* src, FILE* dest) {
    /* Init */
    Map map = mapen_create();
    char c;
    char str[5] = { '\0' };
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

void decode(FILE* src, FILE* dest) {
    printf("Decoding is not yet implemented.\n");
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
