#include "../include/pointcloud.h"

double wcoef; // water flow coefficient
double ecoef; // evaporation coefficient

int main(int argc, char *argv[]) {
    /*  ./watershed <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <seq>
     *  a. ifile is the input file name of the pointcloud file.
     *  b. iter is the integer number of computation steps to perform.
     *  c. iwater is the initial floating point amount of water covering the pointcloud.
     *  d. wcoef is a floating point number between 0.0 and 0.2, which is the water flow
     *  coefficient.e. ecoef is a floating point number between 0.9 and 1.0, which is the evaporation
     *  coefficient.
     *  f. ofilebase is the base filename of the output file. If no seq parameter is given the
     *  output file is simply <ofilebase>.gif, and is the final output of the simulation.
     *  g. seq is a number indicating that every seq number of steps a new output file is
     *  generated with the name <ofilebase><iter step>.gif. A seq number of 1 would
     *  output a new file every step.
     */
    if (argc != 8) {
        printf("Usage: %s <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <seq>\n", argv[0]);
        return 1;
    }

    // Đọc tham số từ argv
    char* ifile = argv[1];
    int iter = atoi(argv[2]);
    double iwater = atof(argv[3]);
    wcoef = atof(argv[4]);
    ecoef = atof(argv[5]);
    char* ofilebase = argv[6];
    int seq = atoi(argv[7]);

    FILE *stream;
    stream = fopen(ifile, "rt");
    if (stream == NULL) {
        printf("File %s not found\n", ifile);
        return 0;
    }

    pointcloud_t *pc = readPointCloudData(stream);
    double maxwd = iwater * 2.5;

    initializeWatershed(pc);             
    watershedAddUniformWater(pc, iwater);

    for (int i = 0; i < iter; i++) {
        if (i % 5 == 0) {
            printf("i: %d\n", i);
        }
        watershedStep(pc);

        if ((seq == 0 && i == iter - 1) || (seq > 0 && (i % seq == 0 || i == iter - 1))) {
            char filename[128];
            if (seq == 0) {
                sprintf(filename, "%s.gif", ofilebase);
            }
            else {
                sprintf(filename, "%s-%d.gif", ofilebase, i);
            }
            imagePointCloudWater(pc, maxwd, filename);
            printf("Saved image: %s\n", filename);
        }
    }

    return 1;
}

