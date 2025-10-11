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
 * Complete the 'processCouponStackOperations' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts STRING_ARRAY operations as parameter.
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
 
 typedef struct stackno{
    int valor;
    struct stackno* next;
 }StackNo;
 
 typedef struct stack{
    StackNo* head;
    StackNo* min; //menor
 }Stack;
 
 
 
Stack* cria_stack(){
    Stack* p;
    p = (Stack*) malloc(sizeof(Stack));
    p->head = NULL;
    p->min = NULL;
    
    return p;
 }
 
void push(Stack* s, int val){
    StackNo* ptr;
    ptr = (StackNo*) malloc(sizeof(StackNo));
    
    ptr->valor = val;
    ptr->next = s->head;
    if(s->min == NULL || val < s->min->valor){
        s->min = ptr;
    }
     
    s->head = ptr;
    
}

void pop(Stack* s){
    
    StackNo* trav;
    trav = s->head;
    s->head = trav->next;
    
    if(trav == s->min){
        StackNo* trav2;
        trav2 = s->head;
        s->min = trav2;
        while(trav2 != NULL){
            if(s->min->valor > trav2->valor){
                s->min = trav2;
            }
            trav2 = trav2->next;
        }
        
    }
    
    free(trav);
    
}

int getmin(Stack* s){
    return s->min->valor;
}

int gettop(Stack* s){
    return s->head->valor;
}

 
int* processCouponStackOperations(int operations_count, char** operations, int* result_count) {
    int local_array[operations_count]; //vetor local pra guardar numeros retornados

    if(operations_count == 0){
        return NULL;
    }
    Stack* s = cria_stack();
    int idx = -0; //tamanho do vetor local
    int valor_push;
    for(int i = 0; i < operations_count; i++){
        if(strcmp(operations[i], "getMin") == 0){
            int min = getmin(s);
            local_array[idx++] = min;
        }
        else if(strcmp(operations[i], "pop") == 0){
            pop(s);
        }
        else if(strcmp(operations[i], "top") == 0){
            int top = gettop(s);
            local_array[idx++] = top;
        }
        else if (sscanf(operations[i], "push %d", &valor_push) == 1) {
                push(s, valor_push);
        }
    }
    
    *result_count = idx;
    
    int* a;
    
    a = (int*) malloc(idx * sizeof(int));
    
    for(int i = 0; i < idx; i++){
        *(a + i) = local_array[i];
    } 
    
    return a;
       
}


int main()
{
    int operations_count = parse_int(ltrim(rtrim(readline())));

    char** operations = malloc(operations_count * sizeof(char*));

    for (int i = 0; i < operations_count; i++) {
        char* operations_item = readline();

        *(operations + i) = operations_item;
    }

    int result_count;
    int* result = processCouponStackOperations(operations_count, operations, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%d", *(result + i));

        if (i != result_count - 1) {
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
