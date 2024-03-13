#ifndef LIST_MAN_H
#define LIST_MAN_H

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    int size;
} List;

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

typedef struct ListManager {
    void* (*f_hash)(void*);
    void (*f_print)(struct ListManager*);
    int (*f_comp)(void*, void*);                        
    HashNode* hashList;                                   
} ListManager;

ListManager* createManager(void* (*f_hash)(void*), void
 (*f_print)(ListManager*), int (*f_comp)(void*, void*));

Node* createNode(void* data);

HashNode* createHashNode(void* hash);

void print(ListManager* manager);

void insert(void* data, ListManager* manager);

void* get_value(void* hash, ListManager* manager);

void delete_value(void* hash, ListManager* manager);

void clean_manager(ListManager* manager);

#endif