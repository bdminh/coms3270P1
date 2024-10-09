#include "../include/util.h"
#include "../include/pointcloud.h"

void *allocateArray(int rows, int columns) {
    // default columns is 3
    // 3x3 => 9
    double* array = calloc((rows * columns), sizeof(double));

    if (array == NULL) { // fail malloc
        return NULL;
    }

    return array; 
}

int listInit(List* l, int max_elmt_size) {
    int max_size = 10;

    l->max_size = max_size;  
    l->max_element_size = max_elmt_size;
    l->size = 0;
    
    void* temp = malloc(l->max_size * l->max_element_size);
    if (!temp) {
        printf("Memory data Allocation Failed\n");
        return 0;
    }
    l->data = temp;

    return 1;
}

void listAddEnd(List* l, void* elmt) {
    if (sizeof(elmt) > l->max_element_size) {
        printf("Size of elmt geater than max_element_size");
        return;
    }

    if (l->size == l->max_size) {
        void *temp = l->data;
        l->max_size <<= 1;
        l->data = realloc(l->data, l->max_size * l->max_element_size); 
        if(!l->data) { 
            printf("Out of Memory\n"); 
            l->data = temp; 
            return; 
        }
    }

    *((pcd_t*)l->data + l->size) = *(pcd_t *)elmt;
    l->size++;
}

void *listGet(List* l, int index) {
    void* result = (pcd_t *)l->data + index;
    return result;
}


