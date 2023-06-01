/********************************************************************
 * FILE: pcb.h
 *
 * DESCRIPTION:
 *    Defines the PCB struct used by the schedulers.
 *
 * AUTHOR: William Burroughs
 * DATE: 02202023
 *
 ********************************************************************/

#ifndef PCB_H
#define PCB_H

typedef struct PCB_st {
    int ProcId;
    int ProcPR;
    int CPUburst;
    int myReg[8];
    int queueEnterClock, waitingTime;
    struct PCB_st *next;
} PCB;

#endif
