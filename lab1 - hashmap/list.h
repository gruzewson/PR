#ifndef LIST_H
#define LIST_H

typedef struct Node {
    void* data;
    //struct Node* prev;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    int size;
} List;

Node* createNode(void* data);

List* createList();

void insert_to_list(List* list, void* data, int position);

//void remove(List* list, int position);

void print_list(List* list, void (*f_print)(void *));

void freeList(List* list);

#endif