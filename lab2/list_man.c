#include "list_man.h"
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

void print(ListManager* manager) 
{
    HashNode* currentHash = manager->hashList;
    int index = 0;
    while (currentHash != NULL) 
    {
        printf("Hash[%d]: %d\n", index, *((int*)currentHash->hash));
        index++;
        printf("Values: ");

        Node* currentList = currentHash->list;
        while (currentList != NULL) {
            manager->f_print(currentList->data);
            currentList = currentList->next;
        }
        printf("\n");
        currentHash = currentHash->next;
    }
    printf("--------------------------------------\n");
}

void insert(void* data, ListManager* manager)
{
    void* hash = manager->f_hash(data);
    HashNode* current = manager->hashList;
    HashNode* prev = NULL;

    while(current != NULL && manager->f_comp(hash, current->hash) == 1) 
    {
        prev = current;
        current = current->next;
    }

    //if exists
    if(current != NULL && manager->f_comp(hash, current->hash) == 0) 
    {
        free(hash);
        Node* node = createNode(data);
        node->next = current->list;
        current->list = node;
    }
    else{
        HashNode* node = createHashNode(hash);
        node -> list = createNode(data);

        if(prev == NULL) {
            node->next = manager->hashList;
            if(manager->hashList != NULL) {
                manager->hashList->prev = node;
            }
            manager->hashList = node;
        } else {
            node->next = current;
            node->prev = prev;
            if (prev->next != NULL)
                current->prev = node;
            prev->next = node;
        }
    }
}

void* get_value(void* hash, ListManager* manager)
{
    HashNode* current = manager->hashList;
    while(current != NULL && manager->f_comp(hash, current->hash) != 0) {
        current = current->next;
    }
    if(current == NULL) {
        printf("\n wrong hash\n");
        return NULL;
    }
    Node* node = current->list;
    return node->data;
}

void delete_value(void* hash, ListManager* manager)
{
    HashNode* current_hash = manager->hashList;
    //search for the hash
    while(current_hash != NULL && manager->f_comp(hash, current_hash->hash) != 0) {

        current_hash = current_hash->next;
    }

    if(current_hash == NULL) 
    {
        printf("\n wrong hash\n");
        return;
    }

    //find the last node in the list
    Node* prev = NULL;
    Node* current_node = current_hash->list;
    while (current_node != NULL && current_node->next != NULL) 
    {
        prev = current_node;
        current_node = current_node->next;
    }

    if (prev == NULL)
        current_hash->list = NULL; // If only one node in the list
    else
        prev->next = NULL;
    printf("\nDeleted value successfully\n");
    free(current_node);

    //if the list is empty delete the hash node
    if (current_hash->list == NULL) 
    {
        if (current_hash->prev == NULL)
            manager->hashList = current_hash->next;
        else
            current_hash->prev->next = current_hash->next;

        if (current_hash->next != NULL)
            current_hash->next->prev = current_hash->prev;

        free(current_hash->hash);
        free(current_hash);
    }

}

void clean_manager(ListManager* manager)
{
    HashNode* current_hash = manager->hashList;
    while (current_hash != NULL) 
    {
        Node* current_node = current_hash->list;
        while (current_node != NULL) 
        {
            Node* next = current_node->next;
            free(current_node);
            current_node = next;
        }
        HashNode* next = current_hash->next;
        free(current_hash->hash);
        free(current_hash);
        current_hash = next;
    }
    free(manager);
}


