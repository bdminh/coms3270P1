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
void stat1(FILE * inFile, struct Point* points, int rows);

#endif