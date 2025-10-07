#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);



/*
 * Complete the 'findNextGreaterElementsWithDistance' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY readings as parameter.
 */

/*
 * To return the 2d integer array from the function, you should:
 *     - Store the number of rows of the array to be returned in the result_rows variable
 *     - Store the number of columns of the array to be returned in the result_columns variable
 *     - Allocate the array dynamically
 *
 * For example,
 * int** return_2d_integer_array(int* result_rows, int* result_columns) {
 *     *result_rows = 2;
 *     *result_columns = 3;
 *
 *     int** a = malloc(2 * sizeof(int*));
 *
 *     for (int i = 0; i < 2; i++) {
 *         *(a + i) = malloc(3 * sizeof(int));
 *
 *         for (int j = 0; j < 3; j++) {
 *             *(*(a + i) + j) = 3 * i + j + 1;
 *         }
 *     }
 *
 *     return a;
 * }
 *
 */
int** findNextGreaterElementsWithDistance(int readings_count, int* readings, int* result_rows, int* result_columns) {
    
    *result_rows = readings_count;
    *result_columns = 2;
    
    int** return_array = malloc(*result_rows * sizeof(int*));
    
    for(int i = 0; i < readings_count; i++){
        *(return_array + i) = malloc(2 * sizeof(int));
    }
    
    
    for(int i = 0; i < readings_count; i++){
        int value;
        int distance = 0;
        for(int k = i; k < readings_count; k++){
            if(readings[k] > readings[i]){
                value = readings[k];
                distance = k - i;
                break;
            }
        }
        if(distance == 0){
            value = -1;
            distance = -1;
        }
        
        return_array[i][0] = value;
        return_array[i][1] = distance;
        
    }
    
    return return_array;

}

int main()
{
    int readings_count = parse_int(ltrim(rtrim(readline())));

    int* readings = malloc(readings_count * sizeof(int));

    for (int i = 0; i < readings_count; i++) {
        int readings_item = parse_int(ltrim(rtrim(readline())));

        *(readings + i) = readings_item;
    }

    int result_rows;
    int result_columns;
    int** result = findNextGreaterElementsWithDistance(readings_count, readings, &result_rows, &result_columns);

    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_columns; j++) {
            printf("%d", *(*(result + i) + j));

            if (j != result_columns - 1) {
                printf(" ");
            }
        }

        if (i != result_rows - 1) {
            printf("\n");
        }
    }

    printf("\n");

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
