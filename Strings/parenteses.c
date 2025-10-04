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
 * Complete the 'areBracketsProperlyMatched' function below.
 *
 * The function is expected to return a BOOLEAN.
 * The function accepts STRING code_snippet as parameter.
 */

bool areBracketsProperlyMatched(char* code_snippet) {
    int len = strlen(code_snippet);
    char pilha[len];
    
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = code_snippet[i];

        if (c == '(' || c == '[' || c == '{') {
            pilha[++top] = c;
        } 
        else if (c == ')' || c == ']' || c == '}') {
            if (top < 0) return false; 

            char ult = pilha[top--];
            if ((c == ')' && ult != '(') || (c == ']' && ult != '[') ||(c == '}' && ult != '{')) {
                return false;
            }
        }
    }

    return (top == -1);
    
}

int main()
{
    char* code_snippet = readline();

    bool result = areBracketsProperlyMatched(code_snippet);

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
