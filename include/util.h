#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/bmp.h"

//#define CELL_PER_ROW 3;
#define CELL(row, col) (col + (row * 3)); // 3 is CELL_PER_ROW

typedef struct {
    int max_size; // the current maximum possible size of the list
    int max_element_size; // the maximum size of any element in the array = column
    void* data; // a pointer to the current array containing data
    int size; // the current number of elements in the list = index of element
} List;

void *allocateArray(int rows, int columns);
int listInit(List* l, int max_elmt_size);
void listAddEnd(List* l, void* elmt);
void *listGet(List* l, int index);
List *readPointCloudData(FILE *stream);

#endif


