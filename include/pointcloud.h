#ifndef pointcloud_h
#define pointcloud_h

#include "../include/util.h"

typedef struct {
    double x;
    double y;
    double z;
    double wd;
    void* north;
    void* south;
    void* east;
    void* west;
} pcd_t;

// Khai báo prototype sử dụng struct pointcloud_t
typedef struct pointcloud {
    List* points;
    int rows;
    int cols;
} pointcloud_t;

int findMin(pcd_t* points, int rows);
int findMax(pcd_t* points, int rows);
double sumHeight(pcd_t* points, int rows);
double averageHeight(pcd_t* points, int rows);
void stat1(FILE* inFile, pcd_t* points, int rows);
double* initPixel(List* l, int minHeight, int maxHeight);
int getIndex(List* l, double* a, int minHeight, int maxHeight, int currentIndex);
pointcloud_t* readPointCloudData(FILE *stream);
void imagePointCloud(pointcloud_t* pc, char* filename);
int initializeWatershed(pointcloud_t* pc);
void watershedAddUniformWater(pointcloud_t* pc, double amount);
void watershedStep(pointcloud_t* pc);
void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename);

#endif