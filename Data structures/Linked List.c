// A simple implementation of genreric linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void *key;
    size_t element_size;
    void (*printFunction)(void *key);
    struct Node *next;
} Node;

typedef struct {
    Node *head;
}LinkedList;

void initLinkedList(LinkedList *list){
    list->head = NULL;
}

Node *createNode(void *key, size_t element_size, void (*printFunction)(void *)){
    Node *node = malloc(sizeof(Node));
    if(node != NULL){
        node->key = malloc(element_size);
        if(node->key != NULL){
            memcpy(node->key, key, element_size);
            node->element_size = element_size;
            node->printFunction = printFunction;
            node->next = NULL;
            return node;
        } else {
            fprintf(stderr, "Erreur while allocating memory\n");
            return NULL;
        }
    } else {
        fprintf(stderr, "Erreur while allocating memory\n");
            return NULL;
    }
}

void freeNode(Node *node){
    free(node->key);
    free(node);
}

int empty(LinkedList *liste){
    return liste->head == NULL;
}

void freeList(LinkedList *list){
    if(!empty(list)){
        Node *current_node = list->head;
        while(current_node != NULL){
            Node *temp = current_node;
            current_node = current_node->next;
            freeNode(temp);
        }
    } else {
        list->head = NULL;
    }
}

void pushFront(LinkedList *list, size_t element_size, void *key, void (*printFunction)(void *)){
    Node *new_element = createNode(key, element_size, printFunction);
    if(new_element != NULL){
        new_element->next = list->head;
        list->head = new_element;
    } else {
        fprintf(stderr, "Erreur while allocating memory\n");
        return;
    }

}

void *topFront(LinkedList *list){
    if(!empty(list)){
        return list->head->key;
    } else {
        fprintf(stderr, "Error: the list is empty\n");
    }
}

void popFront(LinkedList *list){
    if(!empty(list)){
        Node *element_to_delete = list->head;
        list->head = element_to_delete->next;
        freeNode(element_to_delete);
    } else {
        fprintf(stderr, "Error: the list is empty\n");
    }
}

void pushBack(LinkedList *list, size_t element_size, void *key, void (*printFunction)(void *)){
    if(!empty(list)){
        Node *current_node = list->head;
        while(current_node->next != NULL){
            current_node = current_node->next;
        }
        current_node->next = createNode(key, element_size, printFunction);
        if(current_node->next == NULL){
            fprintf(stderr, "Error while allocating memory\n");
        }
    } else {
        list->head = createNode(key, element_size, printFunction);
        if(list->head == NULL){
            fprintf(stderr, "Error while allocating memory\n");
        }
    }
}

void *topBack(LinkedList *list){
    if(!empty(list)){
        Node *current_node = list->head;
        while(current_node->next != NULL){
            current_node = current_node->next;
        }
        return current_node->key;
    } else {
        fprintf(stderr, "Error: the list is empty\n");
        return NULL;
    }
}

void popBack(LinkedList *list){
    if(!empty(list)){
        Node *current_node = list->head;
        if(current_node->next == NULL){
            freeNode(current_node);
            list->head = NULL;
        } else {
            while(current_node->next->next != NULL){
                current_node = current_node->next;
            }
            freeNode(current_node->next);
            current_node->next = NULL;
        }
    } else {
        fprintf(stderr, "Error: the list is empty\n");
    }
}

int find(LinkedList *list, void *key){
    if(!empty(list)){
        Node  *current_node = list->head;
        do{
            if(memcmp(current_node->key, key, current_node->element_size) == 0){
                return 1;
            }
            current_node = current_node->next;
        } while(current_node != NULL);
    }
    return 0;
}

void erase(LinkedList *list, void *key){
    if(!empty(list)){
        Node *current_node = list->head;
        if(memcmp(current_node->key, key, current_node->element_size) == 0){
            list->head = current_node->next;
            freeNode(current_node);
        } else {
            while(memcmp(current_node->next->key, key, current_node->element_size) != 0){
                current_node = current_node->next;
            }
            Node *node_to_delete = current_node->next;
            current_node->next = node_to_delete->next;
            freeNode(node_to_delete);
        }
    } else {
        fprintf(stderr, "Error: the list is empty\n");
    }
}

void addBefore(LinkedList *list, Node *node, void  *key, size_t element_size, void (*printFunction)(void *)){
    if(!empty(list)){
        Node *new_element = createNode(key, element_size, printFunction);
        if(new_element == NULL){
            fprintf(stderr, "Error while allocating memory\n");
        }
        Node *current_node = list->head;
        if(memcmp(current_node->key, node->key, current_node->element_size) == 0){
            new_element->next = current_node;
            list->head = new_element;
        } else {
            while(memcmp(current_node->next->key, node->key, current_node->element_size) != 0){
                current_node = current_node->next;
            }
            new_element->next = current_node->next;
            current_node->next = new_element;
        }
    } else {
        fprintf(stderr, "Error: the list is empty\n");
    }
}

void printList(LinkedList *list) {
    if (!empty(list)) {
        Node *current_node = list->head;
        printf("[");
        while (current_node != NULL) {
            current_node->printFunction(current_node->key);
            if (current_node->next != NULL) {
                printf(", ");
            }
            current_node = current_node->next;
        }
        printf("]\n");
    } else {
        printf("[]\n");
    }
}

void printListInt(void *key) {
    printf("%d", *(int *)key);
}

void printListFloat(void *key) {
    printf("%.2f", *(float *)key);
}

void printListString(void *key) {
    printf("\"%s\"", (char *)key);
}

// int main() {
//     LinkedList list;
//     initLinkedList(&list);

//     printf("=== TEST: pushFront ===\n");
//     int x = 10, y = 20, z = 30;
//     pushFront(&list, sizeof(int), &x, printListInt);
//     pushFront(&list, sizeof(int), &y, printListInt);
//     pushFront(&list, sizeof(int), &z, printListInt);
//     printList(&list);

//     printf("\n=== TEST: topFront ===\n");
//     int *topF = (int *)topFront(&list);
//     if (topF) printf("Top Front: %d\n", *topF); 

//     printf("\n=== TEST: popFront ===\n");
//     popFront(&list);
//     printList(&list); 

//     printf("\n=== TEST: pushBack ===\n");
//     int a = 40, b = 50;
//     pushBack(&list, sizeof(int), &a, printListInt);
//     pushBack(&list, sizeof(int), &b, printListInt);
//     printList(&list); 

//     printf("\n=== TEST: topBack ===\n");
//     int *topB = (int *)topBack(&list);
//     if (topB) printf("Top Back: %d\n", *topB); 

//     printf("\n=== TEST: popBack ===\n");
//     popBack(&list);
//     printList(&list); 

//     printf("\n=== TEST: find ===\n");
//     int searchValue = 10;
//     if (find(&list, &searchValue))
//         printf("Value %d found in the list.\n", searchValue);
//     else
//         printf("Value %d not found in the list.\n", searchValue);

//     printf("\n=== TEST: erase ===\n");
//     int eraseValue = 10;
//     erase(&list, &eraseValue);
//     printList(&list); 

//     printf("\n=== TEST: addBefore ===\n");
//     int newElement = 25;
//     Node *targetNode = list.head->next; 
//     addBefore(&list, targetNode, &newElement, sizeof(int), printListInt);
//     printList(&list); 

//     // Tests avec un autre type
//     printf("\n=== TEST with float ===\n");
//     LinkedList floatList;
//     initLinkedList(&floatList);

//     float f1 = 1.1, f2 = 2.2, f3 = 3.3;
//     pushFront(&floatList, sizeof(float), &f1, printListFloat);
//     pushBack(&floatList, sizeof(float), &f2, printListFloat);
//     pushBack(&floatList, sizeof(float), &f3, printListFloat);
//     printList(&floatList); 

//     printf("\n=== Cleanup ===\n");
//     freeList(&list);
//     freeList(&floatList);

//     return 0;
// }