#include "../include/pointcloud.h"  

pointcloud_t* readPointCloudData(FILE *stream) {
    pointcloud_t* result = malloc(sizeof(pointcloud_t));

    if (!result) {
        printf("Failed to allocate memory for pointcloud_t\n");
        return NULL;
    }

    result->points = malloc(sizeof(List));
    if (!result->points) {
        printf("Failed to allocate memory for points list\n");
        free(result);
        return NULL;
    }

    int columns;
    if (fscanf(stream, "%d", &columns) != 1) {
        printf("Failed to read columns\n");
        free(result->points);
        free(result);
        return NULL;
    }
    result->cols = sqrt(columns);
    result->rows = result->cols;

    int temp = listInit(result->points, sizeof(pcd_t));
    if (temp == 0) {
        printf("\nreadPointCloudData: Can not init list\n");
        free(result->points);
        free(result);
        return NULL; 
    }

    for (int i = 0; i < columns; i++) {
        pcd_t *p = (pcd_t *)malloc(sizeof(pcd_t));

        if (!p) continue;

        if (fscanf(stream, "%lf %lf %lf", &p->x, &p->y, &p->z) != 3) {
            printf("Failed to read point at line %d\n", i + 1);
            free(p);
            continue;
        }

        listAddEnd(result->points, p);
    }
    
    return result;
}