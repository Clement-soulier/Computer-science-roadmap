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
    array->element_size = element_size;
    array->capacity = capacity;
    array->size = 0;    
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
    }
    void *target = (char *)array->data + (array->size++ * array->element_size);
    memcpy(target, value, array->element_size);
}

void Remove(DynamicArray *array, size_t index){
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