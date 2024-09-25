#ifndef pointcloud_h
#define pointcloud_h

#include <stdio.h>
#include <stdlib.h>

struct Point {
    double x;
    double y;
    double z;
};

int countRow(FILE* inFile);
int findMin(struct Point* points, int rows);
int findMax(struct Point* points, int rows);
double sumHeight(struct Point* points, int rows);
double averageHeight(struct Point* points, int rows);
void stat1(FILE * inFile, struct Point* points, int rows);

#endif