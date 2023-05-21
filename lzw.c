#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
        printf("Encoding is not yet implemented.\n");
    } else if (strcmp("-d", argv[1]) == 0) {
        /* Decode file */
        printf("Decoding is not yet implemented.\n");
    } else {
        printf("First argument must be \"-e\" or \"-d\".\n");
        return 1;
    }
    return 0;
}
