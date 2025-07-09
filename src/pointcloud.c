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

void imagePointCloud(pointcloud_t* pc, char* filename) {
    int width = pc->cols;
    int height = pc->rows;

    Bitmap* b = bm_create(width, height);

    int maxHeight = findMax(pc->points->data, pc->points->size);
    int minHeight = findMin(pc->points->data, pc->points->size);

    double* a = initPixel(pc->points, minHeight, maxHeight);

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
            int index = getIndex(pc->points, a, minHeight, maxHeight, cell);
            char* rgb = malloc(20 * sizeof(char));
            if (!rgb) {
                return;
            }
            sprintf(rgb, "RGB(%d,%d,%d)", index, index, index);

            unsigned int temp = bm_atoi(rgb);
            bm_set(b, *i, *j, temp);
        }
    }

    bm_save(b, filename);
    bm_free(b);
}

int initializeWatershed(pointcloud_t *pc)
{
    if (pc == NULL || pc->points->data == NULL)
        return 1;

    int rows = pc->rows;
    int cols = pc->cols;
    int total = rows * cols;

    for (int i = 0; i < total; i++) {
        pcd_t *p = listGet(pc->points, i);
        p->wd = 0.0;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = i * cols + j;
            pcd_t *p = listGet(pc->points, index);

            p->north = (i > 0) ? listGet(pc->points, (i - 1) * cols + j) : NULL;
            p->south = (i < rows - 1) ? listGet(pc->points, (i + 1) * cols + j) : NULL;
            p->west  = (j > 0) ? listGet(pc->points, i * cols + (j - 1)) : NULL;
            p->east  = (j < cols - 1) ? listGet(pc->points, i * cols + (j + 1)) : NULL;
        }
    }

    return 0;
}

void watershedAddUniformWater(pointcloud_t* pc, double amount)
{
    for (int i = 0; i < pc->points->size; i++) {
        pcd_t* p = listGet(pc->points, i);
        p->wd += amount;
    }
}

extern double wcoef; // water flow coefficient
extern double ecoef; // evaporation coefficient

static inline double flow(double Ce, double Cw, double NeighE, double NeighW) {
    return ((NeighE + NeighW) - (Ce + Cw)) * wcoef;
}

void watershedStep(pointcloud_t* pc)
{
    int n = pc->points->size;

    double* next_wd = malloc(sizeof(double) * n);
    if (!next_wd) {
        fprintf(stderr, "Error: cannot allocate memory for next water depth.\n");
        exit(1);
    }

    // Step 1:  next_wd[] for each point
    for (int i = 0; i < n; i++) {
        pcd_t* p = listGet(pc->points, i);

        double Ce = p->z;
        double Cw = p->wd;
        double total = 0;

        if (p->north)
            total += flow(Ce, Cw, ((pcd_t *)p->north)->z, ((pcd_t *)p->north)->wd);
        if (p->south)
            total += flow(Ce, Cw, ((pcd_t *)p->south)->z, ((pcd_t *)p->south)->wd);
        if (p->east)
            total += flow(Ce, Cw, ((pcd_t *)p->east)->z, ((pcd_t *)p->east)->wd);
        if (p->west)
            total += flow(Ce, Cw, ((pcd_t *)p->west)->z, ((pcd_t *)p->west)->wd);

        total -= Cw * ecoef;

        double new_wd = Cw + total;
        if (new_wd < 0) new_wd = 0;

        next_wd[i] = new_wd;
    }

    // Step 2: Update wd for each point
    for (int i = 0; i < n; i++) {
        pcd_t* p = listGet(pc->points, i);
        p->wd = next_wd[i];
    }
    
    free(next_wd);
}

void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename)
{
    int width = pc->cols;
    int height = pc->rows;

    Bitmap* b = bm_create(width, height);
    if (!b) {
        fprintf(stderr, "Failed to create bitmap\n");
        return;
    }

    int maxHeight = findMax(pc->points->data, pc->points->size);
    int minHeight = findMin(pc->points->data, pc->points->size);

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
            pcd_t* p = listGet(pc->points, cell);

            int row = *i;
            int col = *j;
            int draw_row = row;

            double wd = p->wd;

            // grayscale
            pcd_t * minEle = listGet(pc->points, minHeight);
            pcd_t * maxEle = listGet(pc->points, maxHeight);
            double min_z = minEle->z;
            double max_z = maxEle->z;
            double z_ratio = (p->z - min_z) / (max_z - min_z);
            if (z_ratio < 0) z_ratio = 0;
            if (z_ratio > 1) z_ratio = 1;

            unsigned char base_gray = (unsigned char)(z_ratio * 255);

            // no water -> grayscale
            if (wd <= 0) {
                char* rgb = malloc(20 * sizeof(char));
                if (!rgb) {
                    return;
                }
                sprintf(rgb, "RGB(%d,%d,%d)", base_gray, base_gray, base_gray);
                unsigned int temp = bm_atoi(rgb);
                bm_set(b, draw_row, col, temp);
            }
            else {
                // water:  overlay from white → blue
                double ratio = wd / maxwd;
                if (ratio > 1) ratio = 1;
                if (ratio < 0) ratio = 0;

                // apply color gradient: from background -> blue
                unsigned char r = (unsigned char)(base_gray * (1 - ratio));
                unsigned char g = (unsigned char)(base_gray * (1 - ratio));
                unsigned char blue = 255; // blue maximum

                char* rgb = malloc(20 * sizeof(char));
                if (!rgb) {
                    return;
                }
                sprintf(rgb, "RGB(%d,%d,%d)", r, g, blue);
                unsigned int temp = bm_atoi(rgb);
                bm_set(b, draw_row, col, temp);
            }
        }
    }

    bm_save(b, filename);
    bm_free(b);
}


