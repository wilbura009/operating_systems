// Standard Hdrs
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Custom Hdrs
#include "pcb.h"        // The PCB struct
#include "errExit.h"    // Prints err msg and exit
#include "format.h"     // Formats and prints the output
#include "debug.h"      // Prints info about the linked list
#include "schedulers.h" // Schedulers, LList, and Global variable

int main(int argc, char **argv) { 
    // ./prog -alg FIFO -input input1.txt 
    //    0     1   2     3      4
    if (argc == 1) {
        printf("No args provided.\n\n");
        printHelpMsg();
        exit(0);
    }
    if (argc > 1) {
        if (strcmp(argv[1],"-h") == 0 ) {
            printHelpMsg();
        }
    }

    int i = 0; 
    char sAlgo[BUFSIZ];
    char sInFile[BUFSIZ];
    char sQuantum[BUFSIZ];
    for( i = 0; i < argc; ++i ) {
        if ( strcmp(argv[i], "-alg") == 0 ) {
            strcpy(sAlgo, argv[i+1]);
        }
        if ( strcmp(argv[i], "-input") == 0 ) {
            strcpy(sInFile, argv[i+1]);
        }
        if ( strcmp(argv[i], "-quantum") == 0 ) {
            strcpy(sQuantum, argv[i+1]);
        }
    }

    FILE *fIn = NULL; 
    fIn = fopen( sInFile, "r" );
    if ( fIn == NULL )
        errExit("%s", strerror(errno));

    // else read in the values from the file
    PCB *pcb = (PCB *)malloc(1 * sizeof(PCB));
    int id, pr, burst;
    while ( fscanf(fIn,"%d %d %d", &id, &pr, &burst) != EOF ) {
        insertInitialList(pcb, id, pr, burst);
        //printf("%d, %d, %d\n", id, pr, burst);
    }
    fclose(fIn);
    if (strcmp(sAlgo, "FIFO" ) == 0 ) {
        printHeading(sInFile,sAlgo);
        FIFO_Scheduling();
    } else if (strcmp(sAlgo, "SJF" ) == 0 ) {
        printHeading(sInFile,sAlgo);
        SJF_Scheduling();
    } else if (strcmp(sAlgo, "PR" ) == 0 ) {
        printHeading(sInFile,sAlgo);
        PR_Scheduling();
    } else if (strcmp(sAlgo, "RR" ) == 0 ) {
        printHeading(sInFile,sAlgo);
        RR_Scheduling();
    } 

    //freeList(Head);  /* freed by schedulers */
    free(pcb);
    return EXIT_SUCCESS; 
}

