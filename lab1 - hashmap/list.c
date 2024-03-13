#include "list.h"
#include <stdio.h>
#include <stdlib.h>

Node* createNode(void* data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

List* createList()
{
    List* list = (List*)malloc(sizeof(list));
    list->head = NULL;
    list->tail = NULL;
    int size = 0;
}

void insert_to_list(List* list, void* data, int position) {
    if(position > list->size || position < 0) {
        printf("wrong position\n");
        return;
    }

    Node* node = createNode(data);

    if(list->head == NULL) {
        list->head = node;
        list->tail = node;
        
    } else {
        if (position == 0) {
            node->next = list->head;
            list->head = node;
            
        } else {
            Node* current = list->head;
            for(int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
            if (node->next == NULL) {
                list->tail = node;
            }
        }
    }
    list->size++;
}

/*
void remove(List* list, int position)
{
    if(position >= list->size || position < 0 || list->head == NULL)
    {
        printf("wrong position\n");
        return;
    }


    
}
*/

void print_list(List* list, void (*f_print)(void *)) {
    Node* current = list->head;
    while (current != NULL) {
        f_print(current->data);
        current = current->next;
    }
}

void freeList(List* list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

