#include "../include/pointcloud.h"

int main() {
    FILE *stream;
    char* fname = "./data/test1.xyz";
    stream = fopen(fname, "rt");
    if (stream == NULL) {
        printf("File %s not found\n", fname);
        return 0;
    }

    List *l = readPointCloudData(stream);
    imagePointCloud(l, "./out.gif");

    return 1;
}