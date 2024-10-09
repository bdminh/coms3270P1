#include "../include/pointcloud.h"

int findMin(pcd_t* points, int rows) {
    int index = 0;
    
    for (int i = 1; i < rows; i++) { 
        if (points[i].z < points[index].z) {
            index = i;
        }
    } 

    return index;
}

int findMax(pcd_t* points, int rows) {
    int index = 0;
    
    for (int i = 1; i < rows; i++) { 
        if (points[i].z > points[index].z) {
            index = i;
        }
    } 

    return index;
}

double sumHeight(pcd_t* points, int rows) {
    double sum = 0;

    for (int i = 0; i < rows; i++) { 
        sum = sum + points[i].z;
    } 

    return sum;
}

double averageHeight(pcd_t* points, int rows) {
    double sum = sumHeight(points, rows);
    double average = sum / rows;

    return average;
}

void stat1(FILE * inFile, pcd_t* points, int rows) {

    for (int i = 0; i < rows; i++) {
        pcd_t p;
        fscanf(inFile, "%lf %lf %lf", &p.x, &p.y, &p.z);

        points[i].x = p.x;
        points[i].y = p.y;
        points[i].z = p.z;
        
    }

    int maxHeight = findMax(points, rows);
    int minHeight = findMin(points, rows);
    double average = averageHeight(points, rows);

    printf("The maximum height is: x: %0.15lf, y: %0.15lf, z: %0.15lf\n", points[maxHeight].x, 
                                                                          points[maxHeight].y, 
                                                                          points[maxHeight].z);
    printf("The minimum height is: x: %0.15lf, y: %0.15lf, z: %0.15lf\n", points[minHeight].x, 
                                                                          points[minHeight].y, 
                                                                          points[minHeight].z);
    printf("The average height of all data points is %0.15lf\n", average);
}

double* initPixel(List* l, int minHeight, int maxHeight) {
    int sizeOfPixel = 256;
    double* a = malloc(sizeOfPixel * sizeof(double));

    if (!a) { // fail malloc
        return NULL;
    }

    double minElmt = ((pcd_t *)listGet(l, minHeight))->z;
    double maxElmt = ((pcd_t *)listGet(l, maxHeight))->z;

    double space = (double)(maxElmt - minElmt)/256;

    for (int i = 0; i < sizeOfPixel; i++) {
        a[i] = minElmt + (i * space);
    }

    return a;
}

int getIndex(List* l, double* a, int minHeight, int maxHeight, int currentIndex) {
    int sizeOfPixel = 255;
    int index = -1;

    for (int i = sizeOfPixel; i >= 0; i--) {
        double currentValue = ((pcd_t *)listGet(l, currentIndex))->z;
        if (currentValue >= a[i]) {
            index = i;
            break;
        }
    }

    return index;
}

void imagePointCloud(List* l, char* filename) {
    int width = sqrt(l->size);
    int height = width;

    Bitmap* b = bm_create(width, height);

    int maxHeight = findMax(l->data, l->size);
    int minHeight = findMin(l->data, l->size);

    double* a = initPixel(l, minHeight, maxHeight);

    // khong hieu sao cu vo day la l bi thay doi dia chi
    // => khả năng cao là bộ nhớ cục bộ trong hàm không đủ nên nó đè lên vùng nhớ của các biến trước
    // => phải cấp phát động cho tất cả các biến sau
    int* i = malloc(sizeof(int));
    if (!i) {
        return;
    }
    
    int* j = malloc(sizeof(int));
    if (!j) {
        return;
    }

    for (*i = 0; *i < width; (*i)++) {
        for (*j = 0; *j < height; (*j)++) {
            int cell = CELL(*i, *j);
            int index = getIndex(l, a, minHeight, maxHeight, cell);
            char* rgb = malloc(20 * sizeof(char));
            if (!rgb) {
                return;
            }
            sprintf(rgb, "RGB(%d,%d,%d)", index, index, index);

            unsigned int temp = bm_atoi(rgb);
            bm_set(b, *i, *j, temp);
        }
    }

    // unsigned int bm_rgb(unsigned char R, unsigned char G, unsigned char B);
    // void bm_set(Bitmap *b, int x, int y, unsigned int c);

    bm_save(b, filename);
    bm_free(b);
}


