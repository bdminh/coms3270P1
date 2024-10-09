#include "../include/pointcloud.h"  

List* readPointCloudData(FILE *stream) {
    List* result = malloc(sizeof(List));

    int columns;
    fscanf(stream, "%d", &columns);

    int temp = listInit(result, sizeof(pcd_t));
    if (temp == 0) {
        printf("\nreadPointCloudData: Can not init list\n");
        return NULL; 
    }

    for (int i = 0; i < columns; i++) {
        pcd_t *p = (pcd_t *)malloc(sizeof(pcd_t));

        fscanf(stream, "%lf %lf %lf", &p->x, &p->y, &p->z);
        listAddEnd(result, p);
    }
    
    return result;
}