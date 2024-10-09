#ifndef pointcloud_h
#define pointcloud_h

#include "../include/util.h"

typedef struct {
    double x;
    double y;
    double z;
    double amount;
    void* north;
    void* south;
    void* east;
    void* west;
} pcd_t;

int findMin(pcd_t* points, int rows);
int findMax(pcd_t* points, int rows);
double sumHeight(pcd_t* points, int rows);
double averageHeight(pcd_t* points, int rows);
void stat1(FILE* inFile, pcd_t* points, int rows);
double* initPixel(List* l, int minHeight, int maxHeight);
int getIndex(List* l, double* a, int minHeight, int maxHeight, int currentIndex);
List* readPointCloudData(FILE *stream);
void imagePointCloud(List* l, char* filename);

#endif