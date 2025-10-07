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

typedef struct SinglyLinkedListNode SinglyLinkedListNode;
typedef struct SinglyLinkedList SinglyLinkedList;

struct SinglyLinkedListNode {
    int data;
    SinglyLinkedListNode* next;
};

struct SinglyLinkedList {
    SinglyLinkedListNode* head;
    SinglyLinkedListNode* tail;
};

SinglyLinkedListNode* create_singly_linked_list_node(int node_data) {
    SinglyLinkedListNode* node = malloc(sizeof(SinglyLinkedListNode));

    node->data = node_data;
    node->next = NULL;

    return node;
}

void insert_node_into_singly_linked_list(SinglyLinkedList** singly_linked_list, int node_data) {
    SinglyLinkedListNode* node = create_singly_linked_list_node(node_data);

    if (!(*singly_linked_list)->head) {
        (*singly_linked_list)->head = node;
    } else {
        (*singly_linked_list)->tail->next = node;
    }

    (*singly_linked_list)->tail = node;
}

void print_singly_linked_list(SinglyLinkedListNode* node, char* sep) {
    while (node) {
        printf("%d", node->data);

        node = node->next;

        if (node) {
            printf("%s", sep);
        }
    }
}



/*
 * Complete the 'extractAndAppendSponsoredNodes' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts INTEGER_SINGLY_LINKED_LIST head as parameter.
 */

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
 
void insert(SinglyLinkedList* lista, int data){
    SinglyLinkedListNode* ptr;
    ptr = malloc(sizeof(SinglyLinkedListNode));
    
    ptr->data = data;
    ptr->next = lista->head;
    if(lista->head == NULL){
        lista->tail = ptr;
    }
    lista->head = ptr;
}

void remove_node(SinglyLinkedListNode** head, int data){
    SinglyLinkedListNode* j = NULL; //ponteiro auxiliar
    for(SinglyLinkedListNode* i = *head; i != NULL; i = i->next){
        if(i->data == data){
            if(j != NULL){
                if(i->next == NULL){
                   j->next = NULL;
                }
                else{
                    j->next = i->next;
                }
                free(i);
                break;
            }
            else{
                if(i == *head && i->next != NULL){
                    *head = i->next;
                    free(i);
                    break;
                }
            }
        }
        j = i;
    }
}

void insert_end(SinglyLinkedListNode* head, int data){
    SinglyLinkedListNode* ptr;
    
    ptr = malloc(sizeof(SinglyLinkedListNode));
    
    ptr->next = NULL;
    ptr->data = data;

    
    SinglyLinkedListNode* trav = head;
    while(trav->next != NULL){
        trav = trav->next;
    }
    
    trav->next = ptr;
}

SinglyLinkedListNode* extractAndAppendSponsoredNodes(SinglyLinkedListNode* head) {
    
    SinglyLinkedList* lista2 = malloc(sizeof(SinglyLinkedList)); //lista suporte
    lista2->head = NULL;
    lista2->tail = NULL;
    
    SinglyLinkedListNode* i = head;
    while (i != NULL && i->next != NULL) {
        insert(lista2, i->data);
        i = i->next->next;
    }
    
    for(SinglyLinkedListNode* i = lista2->head; i != NULL; i = i->next){
        remove_node(&head, i->data); //remove da lista antiga
    }
    
    for(SinglyLinkedListNode* i = lista2->head; i != NULL; i = i->next){
        insert_end(head, i->data);
    }
    
    return head;
    
}

int main()
{
    SinglyLinkedList* head = malloc(sizeof(SinglyLinkedList));
    head->head = NULL;
    head->tail = NULL;

    int head_count = parse_int(ltrim(rtrim(readline())));

    for (int i = 0; i < head_count; i++) {
        int head_item = parse_int(ltrim(rtrim(readline())));

        insert_node_into_singly_linked_list(&head, head_item);
    }

    SinglyLinkedListNode* result = extractAndAppendSponsoredNodes(head->head);

    print_singly_linked_list(result, "\n");
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
