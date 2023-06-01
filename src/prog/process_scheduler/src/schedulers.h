/********************************************************************
 * FILE: schedulers.h
 *
 * DESCRIPTION:
 *    This file defines the following:
 *      1. Schedulers: FIFO, SJF, PR and RR.
 *      2. Linked list functions.
 *      3. Global variables needed for the previous two items.
 *
 * AUTHOR: William Burroughs
 * DATE: 02202023
 *
 ********************************************************************/

#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "pcb.h"

// ----- List functions -----
void insertInitialList(PCB *pcb, int id, int pr, int burst);
void freeList(PCB *head);
void rmNodeList(PCB *pMin, int key);

// ----- Formatting and printing output functions -----
void setPerformanceData(PCB *tmp, int quantum);
void printPerformanceData();

// ----- Scheduler functions -----
void FIFO_Scheduling();
PCB *getShortestJob();    // Helper for SJF_Scheduling()
void SJF_Scheduling();
PCB *getMaxProcPR();      // Helper for PR_Scheduling()
void PR_Scheduling();
void insertPCB(PCB *pcb); // Helper for RR_Scheduling()
void RR_Scheduling();

#endif
