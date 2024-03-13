#ifndef HASH_LIST_H
#define HASH_LIST_H
#include "list.h"

typedef struct ListManager ListManager;

typedef struct HashNode {
    void* hash;
    List* list;
    struct HashNode* prev;
    struct HashNode* next;
} HashNode;

typedef struct HashList {
    HashNode* head;
    HashNode* tail;
    int size;
} HashList;

HashNode* createHashNode(void* hash);

HashList* createHashList();

/*
void insertToHash(void* data, ListManager* manager);

//void remove(List* list, int position);

void printHashList(HashList* hashlist, void (*f_print)(void*));

void freeHashList(HashList* hashlist);
*/
#endif