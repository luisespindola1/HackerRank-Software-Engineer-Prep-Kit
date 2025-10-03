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
 * Complete the 'countResponseTimeRegressions' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY responseTimes as parameter.
 */

int countResponseTimeRegressions(int responseTimes_count, int* responseTimes) {
    int count = 0;
    for(int i = 1; i < responseTimes_count; i++){
        float media = 0.0;
        int count_media = 0;
        for(int j = i - 1; j >= 0; j--){
            media += responseTimes[j];
            count_media++;
        }
        if(responseTimes[i] > (media/count_media)){
            count++;
        }
    }    
    
    return count;
}

int main()