#include "../include/pointcloud.h"

int countRow(FILE* inFile) {
    int count = 0;

    struct Point p;
    while(fscanf(inFile, "%lf %lf %lf", &p.x, &p.y, &p.z) > 0) {
        count++;
    }

    return count;
}

void stat1(FILE * inFile, struct Point* points, int rows) {

    for (int i = 0; i < rows; i++) {
        struct Point p;
        fscanf(inFile, "%lf %lf %lf", &p.x, &p.y, &p.z);

        points[i] = p;
    }
    
    for (int i = 0; i < rows; i++) {
        printf("Point %d %.15lf %.15lf %.15lf\n", i, points[i].x, points[i].y, points[i].z);
    }
}

int main() {
    FILE *fpIn;
    char* fname = "./data/input.txt";
    fpIn = fopen(fname, "rt");
    if (fpIn == NULL) {
        printf("File %s not found\n", fname);
        return 0;
    }
    
    int rows = countRow(fpIn);
    printf("Rows: %d\n", rows);
    fclose(fpIn);

    struct Point* points = (struct Point*)malloc(rows * sizeof(*points));

    // print data
    fpIn = fopen(fname, "rt");
    if (fpIn == NULL) {
        printf("File %s not found\n", fname);
        return 0;
    }

    stat1(fpIn, points, rows);
    fclose(fpIn);

    // free the memory when done
    free(points);
    return 1;
}


