#include <stdio.h>
#include <stdlib.h>
#include "list_man.h"

int compareHash(void* hash1, void* hash2) {
    const int* value1 = (int*)hash1;
    const int* value2 = (int*)hash2;
    if (*value1 > *value2)
        return 1;
    else if (*value1 == *value2)
        return 0;
    else return -1;
}

void* hashing_func(void* value) {
    char* hash = (char*)value;
    int sum = 0;

    for (int i = 0; i < strlen(hash); i++) {
        sum += (int)hash[i];
    }

    int* result = (int*)malloc(sizeof(int)); //freeing in insert
    if (result == NULL) {
        printf("malloc failed.\n");
        exit(1);
    }

    *result = sum;
    return result;
}

void print_func(void* data)
{
    printf("%s, ", data);
}

int main() {
    ListManager* manager = malloc(sizeof(ListManager));
    manager->hashList = NULL;
    manager->f_hash = hashing_func;
    manager->f_comp = compareHash;
    manager->f_print = print_func;

    insert("12345", manager);
    insert("dzien dobry", manager);
    insert("przyklad3", manager);
    insert("aabb", manager);
    insert("bbaa", manager);
    insert("rrrr", manager);
    insert("number 3", manager);
    insert("value_1", manager);

    print(manager);

    int y = 732;
    int x = 390;
    int z = 391;
    void* value1 = get_value(&y, manager);
    void* value2 = get_value(&x, manager);
    if (value1 != NULL){
        printf("\nGet value: %s\n", (char*)value1);
    }
    if (value2 != NULL){
        printf("\nGet value: %s\n", (char*)value2);
    }

    delete_value(&z,manager); //invalid
    delete_value(&x,manager);
    delete_value(&y,manager);
    print(manager);
    delete_value(&x,manager);
    print(manager);

    //value = get_value(&x, manager);
    //if (value != NULL)
    //    printf("\nGet value: %s\n", (char*)value);

    clean_manager(manager);
    return 0;
}