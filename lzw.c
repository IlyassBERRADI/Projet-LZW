#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "mapen.h"
#include "mapde.h"
#include "str.h"
#include "bit_io.h"

#define STR_SIZE 10000
#define BITS 9

int power_number(int a, int b){
    int res=1;
    for (size_t i = 0; i < b; i++)
    {
        res*=a;
    }
    return res;
}


/**
 * @brief Encode a given src file in dest file using LZW algorithm.
 */
void encode(FILE* src, FILE* dest) {
    /* Init */
    int max_code_size=12;
    int min_code_size=8;
    int current_code_size=min_code_size+1;
    Map map = mapen_create();
    BIT_FILE *bfout = bit_begin(dest);
    char c;
    Str str = str_create(STR_SIZE);
    int max_size = 0;
    int count_pass = 0;
    int count_add = 0;
    uint32_t code;
    /*fprintf(dest, "%u ", CLEAR_CODE);*/
    bit_put(bfout, CLEAR_CODE, current_code_size);
    c = fgetc(src);
    str_append(str, c);
    
    /* Read file */
    while (!feof(src)) {
        if (mapen_get_code(map, str, &code)) {
            /* Continue reading file */
            c = fgetc(src);
            /* Add char to string */
            str_append(str, c);

            count_pass++;
        } else {
            /* The current str has no code,
            write of previous valid code and creation of a new code */
            /*fprintf(dest, "%u ", code);*/

            bit_put(bfout, code, current_code_size);
            if (!(map->next_code==power_number(2, current_code_size) &&
            current_code_size==max_code_size))
            {
                mapen_add_str(map, str);
                if (map->next_code==power_number(2, current_code_size)+1)
                {
                    current_code_size++;
                }
                
            }
            else
            {
                bit_put(bfout, CLEAR_CODE, current_code_size);
                current_code_size=min_code_size+1;
                map_free(map);
                map=mapen_create();
                map->next_code=258;
            }
            
            /* str is now equals to the last character read */
            str_empty(str);
            str_append(str, c);

            count_add++;
        }

        if (str->size > max_size) max_size = str->size;
    }

    /* Write last string */
    if (str->size > 0) {
        mapen_get_code(map, str, &code);
        /*fprintf(dest, "%u ", code);*/
        bit_put(bfout, code, current_code_size);
    }

    /* Show statistics */
    printf("Maximum size of generated string in the dictionary : %d\n", max_size);
    /*printf("Number of element in the dictionary : %d\n", map_count(map));*/
    printf("Number of element in the dictionary : %d\n", map_count(map));

    /* Close the data */
    /*fprintf(dest, "%u", END_CODE);*/
    bit_put(bfout, END_CODE, current_code_size);
    bit_end(bfout);
    str_free(str);
    map_free(map);
}

/**
 * @brief Manage an array of two pointer to free.
 */
void update_trash(Str trash[], Str str) {
    if (trash[0] != NULL) str_free(trash[0]);
    trash[0] = trash[1];
    trash[1] = str;
}

/**
 * @brief Add to map a new string with last_str and new_char.
 */
void add_to_map(Map map, Str last_str, char new_char) {
    Str to_add = str_copy(last_str, last_str->size + 1);
    str_append(to_add, new_char);
    mapde_add_str(map, to_add);
    str_free(to_add);
}

/**
 * @brief Generate the text corresponding to an unknown code.
 * @param last_str String of the last code read.
 */
Str get_unknown_code(Str last_str) {
    Str str = str_copy(last_str, last_str->size + 1);
    str_append(str, last_str->data[0]);
    return str;
}

/**
 * @brief Decode src file into dest file using LZW algorithm.
 */
void decode(FILE* src, FILE* dest) {
    /* Init */
    Map map=NULL;
    BIT_FILE *bfin = bit_begin(src);
    uint32_t code = 0;
    Str last_str = NULL;
    Str str = NULL;
    Str trash[2] = { NULL };
    int i;
    int max_code_size=12;
    int min_code_size=8;
    int current_code_size=min_code_size+1;
    while (1) {
        /*fscanf(src, "%u", &code);*/
        bit_get(bfin, &code, current_code_size);
        if (code == CLEAR_CODE) {
            /* Create a new map with only default code */
            if (map != NULL) {
                map_free(map);
            }
            map = mapde_create();
            current_code_size=min_code_size+1;
            last_str = NULL;
            str = NULL;
            continue;
        }
        
        /* End of file reached*/
        if (code == END_CODE) {
            break;
        }
        last_str = str;
        
        
        str = mapde_get_str(map, code);
        
        
        if (str == NULL) {
            /* No existing code */
            str = get_unknown_code(last_str);
            update_trash(trash, str);
        }

        str_write(dest, str);

        /* Add a new code */
        if (last_str == NULL){
            continue;
        } 
        add_to_map(map, last_str, str->data[0]);
        if (map->next_code==power_number(2, current_code_size) &&
        current_code_size<max_code_size)
        {
            current_code_size++;
        }
        
        
    }

    /* Free memory */
    map_free(map);
    for (i = 0; i < 2; i++) {
        if (trash[i] != NULL) str_free(trash[i]);
    }
    bit_end(bfin);
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
