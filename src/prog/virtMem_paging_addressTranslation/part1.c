#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include "errExit.h"

void printHelpMsg() {
    printf("USAGE:\n ./prog infile outfile\n");
    exit(0);
}

// ./part1 infile outfile
//    0      1       2
int main(int argc, char **argv) { 
    if (argc < 2) {
        printf("No args provided.\n\n");
        printHelpMsg();
    }
    /* Args exist, check them */
    if (argc == 2) {
        if (strcmp(argv[1],"-help") == 0 )
            printHelpMsg();
    }
    if (argc < 3) {
        printf("outfile missing.\n\n");
        exit(0);
    }

    /* infile and outfile args exist */
    char sInFile[BUFSIZ];
    char sOutFile[BUFSIZ];
    strncpy(sInFile, argv[1], BUFSIZ);  //printf("sInFile  : {%s}\n",sInFile);
    strncpy(sOutFile, argv[2], BUFSIZ); //printf("sOutFile : {%s}\n",sOutFile);

    FILE *fIn = NULL; 
    fIn = fopen(sInFile, "rb");
    if (fIn == NULL)
        errExit("%s: '%s'.", strerror(errno), sInFile);

    FILE *fOut = NULL; 
    fOut = fopen(sOutFile, "wb");
    if (fOut == NULL)
        errExit("%s: '%s'.", strerror(errno), sOutFile);

    unsigned long LA, PA; /* Logical address, Physical address */
    int PT[32] = {2,4,1,7,3,5,6,0}; /* Page table {fNum1,fNum2, ... , 0...} */
    //int p = 5, f = 3, d = 7;
    int d = 7;
    int pNum, fNum, dNum; /* offset */
    int c = 0;

    while (fread(&LA, sizeof(unsigned long), 1, fIn) == 1) {
        dNum = LA & 0x7F;
        pNum = LA >> d;
        fNum = PT[pNum];
        PA = (fNum << d) + dNum; 
        ++c;
        if (argc > 3 && strcmp(argv[3],"-v") == 0 )
            printf("The LA is %-3.lx and the Translated PA is %-3.lx\n", LA, PA);

        fwrite(&PA, sizeof(unsigned long), 1, fOut);
    }
    if (argc > 3 && strcmp(argv[3],"-v") == 0 )
        printf("total number of pages is %d\n", c);

    fclose(fIn);
    fclose(fOut);

    return EXIT_SUCCESS; 
} 
