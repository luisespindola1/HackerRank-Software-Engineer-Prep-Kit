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



/*
 * Complete the 'isNonTrivialRotation' function below.
 *
 * The function is expected to return a BOOLEAN.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */

bool isNonTrivialRotation(char* s1, char* s2) {
    if (strcmp(s1, s2) == 0) return false; 

    int len = strlen(s1);
    if (len != strlen(s2)) return false;

    char s1_suporte[2 * len + 1];
    strcpy(s1_suporte, s1);
    strcat(s1_suporte, s1);  //concatena string s1 

    return strstr(s1_suporte, s2) != NULL; //checa se a substring s2 esta na versao concatenada de s1
}

int main()
{
    char* s1 = readline();

    char* s2 = readline();

    bool result = isNonTrivialRotation(s1, s2);

    printf("%d\n", result);

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
