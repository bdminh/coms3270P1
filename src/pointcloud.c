#include "../include/pointcloud.h"

int countRow(FILE* inFile) {
    int count = 0;

    struct Point p;
    while(fscanf(inFile, "%lf %lf %lf", &p.x, &p.y, &p.z) > 0) {
        count++;
    }

    return count;
}

int findMin(struct Point* points, int rows) {
    int index = 0;
    
    for (int i = 1; i < rows; i++) { 
        if (points[i].z < points[index].z) {
            index = i;
        }
    } 

    return index;
}

int findMax(struct Point* points, int rows) {
    int index = 0;
    
    for (int i = 1; i < rows; i++) { 
        if (points[i].z > points[index].z) {
            index = i;
        }
    } 

    return index;
}

double sumHeight(struct Point* points, int rows) {
    double sum = 0;

    for (int i = 0; i < rows; i++) { 
        sum = sum + points[i].z;
    } 

    return sum;
}

double averageHeight(struct Point* points, int rows) {
    double sum = sumHeight(points, rows);
    double average = sum / rows;

    return average;
}

void stat1(FILE * inFile, struct Point* points, int rows) {

    for (int i = 0; i < rows; i++) {
        struct Point p;
        fscanf(inFile, "%lf %lf %lf", &p.x, &p.y, &p.z);

        points[i] = p;
    }

    int maxHeight = findMax(points, rows);
    int minHeight = findMin(points, rows);
    double average = averageHeight(points, rows);

    printf("The maximum height is: x: %0.15lf, y: %0.15lf, z: %0.15lf\n", points[maxHeight].x, points[maxHeight].y, points[maxHeight].z);
    printf("The minimum height is: x: %0.15lf, y: %0.15lf, z: %0.15lf\n", points[minHeight].x, points[minHeight].y, points[minHeight].z);
    printf("The average height of all data points is %0.15lf\n", average);
}

int main() {
    FILE *fpIn;
    char* fname = "../data/input1.txt";
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


