#include "hash_list.h"
#include <stdio.h>
#include <stdlib.h>

HashNode* createHashNode(void* hash)
{
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    node->hash = hash;
    node->list = NULL;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

HashList* createHashList()
{
    List* list = (List*)malloc(sizeof(list));
    list->head = NULL;
    list->tail = NULL;
    int size = 0;
}
/*
void insertToHash(void* data, ListManager* manager); {
    HashNode* node = createHashNode(NULL, list);
    node->hash = f_hash(list->head->data, modulo);
    if(list->head == NULL) {
        list->head = node;
        list->tail = node;
        
    } else {
        HashNode* current = list->head;
        while(f_comp(hashlist->head, current) == 1){
                current = current->next;
            }
            node->next = current->next;
            node->prev = current;
            if (current->next != NULL) {
                current->next->prev = node;
            }
            current->next = node;
            if (node->next == NULL) {
                list->tail = node;
            }
        }
    hashlist->size++;
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
 


void printHashList(HashList* hashlist, void (*f_print)(void*)) {
    HashNode* current = hashlist->head;
    while (current != NULL) {
        print(current->list, f_print);
        current = current->next;
    }
}


void freeHashList(HashList* hashlist)
{
    HashNode* current = hashlist->head;
    while (current != NULL)
    {
        HashNode* next = current->next;
        freeList(current->list);
        free(current);
        current = next;
    }
    free(hashlist);
}
*/
