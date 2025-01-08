// A simple implementation of generic dynamic arrays
// Given with some basic operations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    void *data;
    size_t element_size;
    size_t capacity;
    size_t size;
}DynamicArray;

void initArray(DynamicArray *array, size_t element_size, size_t capacity){
    array->data = malloc(capacity * element_size);
    if(array->data != NULL){
        array->element_size = element_size;
        array->capacity = capacity;
        array->size = 0;
    } else {
        fprintf(stderr, "Error while allocating memory\n");
    }
}

void *getElement(DynamicArray *array, size_t index){
    if(index >= array->size){
        fprintf(stderr, "Error: index out of bounds.\n");
        return NULL;
    } 
    return (char *)array->data + (index * array->element_size);
}

void setElement(DynamicArray *array, size_t index, void *value){
    if(index < array->size){
        void * target = (char *)array->data + (index * array->element_size);
        memcpy(target, value, array->element_size);
    } else {
        fprintf(stderr, "Error: index out of bounds.\n");
    }
}

void pushBack(DynamicArray *array, void *value){
    if(array->size == array->capacity){
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * array->element_size);
        if(array->data == NULL){
            fprintf(stderr, "Error while allocating memory\n");
            return;
        }
    }
    void *target = (char *)array->data + (array->size++ * array->element_size);
    memcpy(target, value, array->element_size);
}

void removeAt(DynamicArray *array, size_t index){
    if(index < array->size){
        for(size_t i = index; i < array->size - 1; i++){
            void *target = (char *)array->data + (i * array->element_size);
            void *val_to_cpy = (char *)array->data + ((i + 1) * array->element_size);
            memcpy(target, val_to_cpy, array->element_size);
        }
        array->size--;
    } else {
        fprintf(stderr, "Error: index out of bounds.\n");
    }
}

void removeElement(DynamicArray *array, void *element){
    for(size_t index = 0; index < array->size; index++){
        void *current_element = (char *)array->data + (index * array->element_size);
        if(memcmp(current_element, element, array->element_size) == 0){
            removeAt(array, index);
        }
    }
}

void *pop(DynamicArray *array){
    if(array->size > 0){
        array->size--;
        return (char *)array->data + (array->size * array->element_size);
    } else {
        fprintf(stderr, "Error: index out of bounds.\n");
    }
}

void freeArray(DynamicArray *array){
    free(array->data);
}

void printArrayInt(void *element){
    printf("%i", *(int *)element);
}

void printArrayFloat(void *element){
    printf("%.2f", *(float *)element);
}

void printArrayString(void *element){
    printf("\"%s\"", (char *)element);
}

void printArray(DynamicArray *array, void (*printFunction)(void *)){
    printf("[");
    for(size_t index = 0; index < array->size; index++){
        void *element = (char *)array->data + (index * array->element_size);
        printFunction(element);
        if(index != array->size - 1){
            printf(", ");
        }
    }
    printf("]\n");
}

// int main() {
//     printf("=== DYNAMIC ARRAY TEST ===\n\n");

//     // Initialisation
//     printf("1. Initialising Array with Int\n");
//     DynamicArray array;
//     initArray(&array, sizeof(int), 2);
//     printArray(&array, printArrayInt);

//     // pushBack
//     printf("\n2. Add element with pushBack\n");
//     int x = 10, y = 20, z = 30;
//     pushBack(&array, &x);
//     pushBack(&array, &y);
//     pushBack(&array, &z);
//     printArray(&array, printArrayInt);

//     // setElement
//     printf("\n3. Modifying element with setElement\n");
//     int newValue = 99;
//     setElement(&array, 1, &newValue);
//     printArray(&array, printArrayInt);

//     // getElement
//     printf("\n4. Read element with getElement\n");
//     int *retrievedValue = (int *)getElement(&array, 1);
//     if (retrievedValue) printf("Index 1 contains value: %d\n", *retrievedValue);

//     // popBack
//     printf("\n5. Remove last element with popBack\n");
//     retrievedValue = (int *)pop(&array);
//     printArray(&array, printArrayInt);
//     if (retrievedValue) printf("\nRetrieved value: %d\n", *retrievedValue);

//     // Add few element and print
//     printf("\n7. Add few elements and print\n");
//     int a = 40, b = 50, c = 60;
//     pushBack(&array, &a);
//     pushBack(&array, &b);
//     pushBack(&array, &c);
//     printArray(&array, printArrayInt);

//     // remove
//     printf("\n8. Removing element with remove\n");
//     int elementToDelete = 50;
//     removeElement(&array, &elementToDelete);
//     printArray(&array, printArrayInt);

//     // removeAt
//     printf("\n9. Removing element with removeAt\n");
//     removeAt(&array, 1); // Supprime le premier élément
//     printArray(&array, printArrayInt);

//     // Test with float
//     printf("\n10. Initialising array with float\n");
//     DynamicArray floatArray;
//     initArray(&floatArray, sizeof(float), 3);

//     float f1 = 1.1, f2 = 2.2, f3 = 3.3;
//     pushBack(&floatArray, &f1);
//     pushBack(&floatArray, &f2);
//     pushBack(&floatArray, &f3);
//     printArray(&floatArray, printArrayFloat);

//     // Cleanup
//     printf("\n11. Cleanup\n");
//     freeArray(&array);
//     freeArray(&floatArray);

//     return 0;
// }