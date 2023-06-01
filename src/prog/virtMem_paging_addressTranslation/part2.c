#include <stdarg.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include "errExit.h"

typedef struct PageTable {
    int fNum;    /* frame number     */
    int vi;      /* valid or invalid */
} PT;

void printHelpMsg() {
    printf("USAGE:\n ./prog infile outfile\n");
    exit(0);
}

/*
 * Helper for openFile().
 */
int errCkFile(FILE *fp, char *sFNm) {
    if (fp == NULL)
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}

/*
 * NOTE:
 * - Exits on failure.
 * - errCkFile() is a helper for this.
 */
FILE *openFile(char *sFNm, char const *sFMode) {
    FILE *fp = NULL;
    fp = fopen(sFNm, sFMode);

    if(errCkFile(fp, sFNm) == EXIT_FAILURE)
        errExit("%s: '%s'.", strerror(errno), sFNm);

    return fp;
}

int getFreeFrame(int *frFrms, int arrSz) {
    int i, iFrm = -1;
    for (i = 0; i < arrSz; ++i) {
        if (frFrms[i] == 1) { /* frame at index i is free */
            iFrm = i;         /* set return var to free frame index */
            frFrms[iFrm] = 0; /* set frame as used */
            break; 
        }
    }
    return iFrm; 
}

int getTargetLRU(int *LRUct, int arrSz) {
    int minVal = LRUct[1]; 
    int minFrm = 1; /* 0 is for OS */
    for (int i = 1; i < arrSz; ++i) {
        //printf("(LRUct[%d] < min) => (%d < %d) => ", i, LRUct[i], minVal);
        if (LRUct[i] < minVal) {
            minVal = LRUct[i];
            minFrm = i;
        }
        //printf("%d\n", minVal);
    }
    //printf("%d\n", minFrm);
    return minFrm;
}

int main(int argc, char **argv) { 

    if (argc != 3)
        printHelpMsg();

    /* infile and outfile args exist */
    char sInFile[BUFSIZ], sOutFile[BUFSIZ];
    strncpy(sInFile, argv[1], BUFSIZ);  //printf("sInFile  : {%s}\n",sInFile);
    strncpy(sOutFile, argv[2], BUFSIZ); //printf("sOutFile : {%s}\n",sOutFile);

    FILE *fIn = NULL, *fOut = NULL; 
    fIn = openFile(sInFile, "rb");
    fOut = openFile(sOutFile, "wb");

    /*** Part2 ***/
    struct PageTable PT[32];
    unsigned long LA, PA; /* Logical address, Physical address */
    //unsigned int p = 5, f = 3, d = 7;
    unsigned int d = 7;
    unsigned int pNum, fNum, dNum; /* offset */
    int CLK = 0;
    /* NOTE: freeFrames[0] is for OS. */
    int freeFrames[8] = { 0, 1, 1, 1,
                          1, 1, 1, 1  };
    int LRUcount[8] = {0};
    int revMap[8] = {-1};

    /* set all valid/invalid fields in page table to 0 */
    for (int i = 0; i < 32; ++i)
        PT[i].vi = 0;

    int x = 0; /* used with getFreeFrame() */
    int y = 0; /* used with getTargetLRU() */
    int pgFaultCt = 0;
    while (fread(&LA, sizeof(unsigned long), 1, fIn) == 1)
    {
        ++CLK;
        dNum = LA & 0x7F;
        pNum = LA >> d;
        if (PT[pNum].vi == 1) /* page num. has a valid bit */
        {
            fNum = PT[pNum].fNum;
            PA = (fNum << d) + dNum; 
            fwrite(&PA, sizeof(unsigned long), 1, fOut); // TODO: err
            LRUcount[fNum] = CLK;
        }
        else {
            ++pgFaultCt;
            x = getFreeFrame(freeFrames, 8);
            if (x > 0)
            {
                PT[pNum].fNum = x;
                PT[pNum].vi = 1;
                fNum = PT[pNum].fNum;
                PA = (fNum << d) + dNum; 
                fwrite(&PA, sizeof(unsigned long), 1, fOut); // TODO: err
                freeFrames[x] = 0;
                revMap[x] = pNum;
                LRUcount[fNum] = CLK;
            }
            else { /* x < 0 : Use the LRU policy for page replacement */
                y = getTargetLRU(LRUcount, 8);
                PT[revMap[y]].vi = 0;
                PT[pNum].fNum = y;
                PT[pNum].vi = 1;
                fNum = PT[pNum].fNum; /* is y */
                PA = (fNum << d) + dNum; 
                fwrite(&PA, sizeof(unsigned long), 1, fOut); // TODO: err
                revMap[fNum] = pNum;
                LRUcount[fNum] = CLK;
            }
        }
    }
    printf("Part 2 page faults: %d\n", pgFaultCt);

    fclose(fIn);
    fclose(fOut);
    return EXIT_SUCCESS; 
} 
