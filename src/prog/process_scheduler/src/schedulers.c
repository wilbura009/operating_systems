#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "debug.h"

int CPUreg[8]={0};
PCB *Head=NULL;
PCB *Tail=NULL; 
int CLOCK=0;
int Total_waiting_time=0;
int Total_turnaround_time=0;
int Total_job=0;
int quantum=0;

// insert at the end of the list
void insertInitialList(PCB *pcb, int id, int pr, int burst) {
    PCB *node = (PCB*) malloc(sizeof(PCB));
    Tail = Head;

    node->ProcId = id;
    node->ProcPR = pr;
    node->CPUburst = burst;
    for(int k=0; k < 8; k++) node->myReg[k] = id;
    node->queueEnterClock = 0;
    node->waitingTime = 0;

    node->next = NULL; // will be last node
    if (Head == NULL) { // list is empty insert 
        Head = node;
        return;
    }
    while (Tail->next != NULL)
        Tail = Tail->next;
    
    Tail->next = node;
}

void freeList(PCB *head) {
    PCB *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

/* Helper for:
 * - SJF_Scheduling()
 * - PR_Scheduling()
 **/
void rmNodeList(PCB *pMin, int key) {
    PCB *pPrev, *tmp;
    tmp = Head; // store the head
    
    // key is in the head
    if ( (tmp != NULL) && (tmp->ProcId == key) ){
        Head = tmp->next;
        free(tmp);
        return;
    }
    // searching for the key in the list
    while (tmp != NULL && tmp->ProcId != key) {
        pPrev = tmp;
        tmp = tmp->next;
    }
    pPrev->next = tmp->next; // unlink from list
    free(tmp);
}

/* Data Collection for performance metrics */
void setPerformanceData(PCB *tmp, int quantum) {
    if (quantum == 0) {
        tmp->waitingTime = tmp->waitingTime + CLOCK - tmp->queueEnterClock;
        Total_waiting_time = Total_waiting_time + tmp->waitingTime;
        CLOCK = CLOCK + tmp->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1; 
    }
    else {
        tmp->waitingTime = tmp->waitingTime + CLOCK - tmp->queueEnterClock;
        CLOCK = CLOCK + quantum;
        tmp->CPUburst = tmp->CPUburst - quantum;
        tmp->queueEnterClock = CLOCK;
    }
}

void printPerformanceData(){
    double avgWait = (double) Total_waiting_time / Total_job;
    printf("\nAverage Waiting time =  %.2f ms  (%d/%d)\n",
            avgWait, Total_waiting_time, Total_job);
    double turnAround = (double) Total_turnaround_time / Total_job;
    printf("Average Turnaround time =  %.2f ms  (%d/%d)\n",
            turnAround, Total_turnaround_time, Total_job);
    double throughput = (double) Total_job / CLOCK;
    printf("Throughput =  %.2f ms  (%d/%d)\n",
            throughput, Total_job, CLOCK);
}

void FIFO_Scheduling() {
    PCB *tmp;
    while (Head != NULL) {
        tmp = Head;
        Head = Head->next;
        
        for(int i=0; i < 8; i++) {
            CPUreg[i] = tmp->myReg[i]; // context switching
            CPUreg[i] = CPUreg[i] + 1; // work done by cpu
            tmp->myReg[i] = CPUreg[i];
        }
        setPerformanceData(tmp, quantum); //printf("\t\t\ttmp->CPUburst: %d\n",tmp->CPUburst);
        printf("Process %d is completed at %d ms\n", tmp->ProcId, CLOCK);
        free(tmp);
    }
    printPerformanceData();
}

// Helper for SJF_Scheduling()
PCB *getShortestJob() {
    PCB *pMin = Head; 
    PCB *pCurr = Head;

    while (pCurr != NULL) {
        if (pCurr->CPUburst < pMin->CPUburst)
            pMin = pCurr;

        pCurr = pCurr->next;
    }
    return pMin;
}

void SJF_Scheduling(){
    PCB *pMin;
    pMin = getShortestJob();
    while (pMin != NULL) {
        for(int i=0; i < 8; i++) {
            CPUreg[i] = pMin->myReg[i]; // context switching
            CPUreg[i] = CPUreg[i] + 1;  // work done by cpu
            pMin->myReg[i] = CPUreg[i];
        }
        setPerformanceData(pMin, quantum); //printf("\t\t\ttmp->CPUburst: %d\n",tmp->CPUburst);
        printf("Process %d is completed at %d ms\n", pMin->ProcId, CLOCK);
        rmNodeList(pMin, pMin->ProcId);
        pMin = getShortestJob();
    }
    printPerformanceData();
}

// Helper for PR_Scheduling()
PCB *getMaxProcPR(){
    PCB *pMax = Head; 
    PCB *pCurr = Head;

    while (pCurr != NULL) {
        if (pCurr->ProcPR < pMax->ProcPR)
            pMax = pCurr;

        pCurr = pCurr->next;
    }
    return pMax;
}

void PR_Scheduling(){
    PCB *pMax;
    pMax = getMaxProcPR();
    while (pMax != NULL) {
        for(int i=0; i < 8; i++) {
            CPUreg[i] = pMax->myReg[i]; // context switching
            CPUreg[i] = CPUreg[i] + 1;  // work done by cpu
            pMax->myReg[i] = CPUreg[i];
        }
        setPerformanceData(pMax, quantum); //printf("\t\t\ttmp->CPUburst: %d\n",tmp->CPUburst);
        printf("Process %d is completed at %d ms\n", pMax->ProcId, CLOCK);
        rmNodeList(pMax, pMax->ProcId);
        pMax = getMaxProcPR();
    }
    printPerformanceData();
}

// Helper for RR_Scheduling()
// FIXME: Causes segfault
void insertPCB(PCB *pcb){
    /*
    // pcb is already at the end of the list
    if (Tail == pcb) {
        return;
    // pcb is at the beginning of the list
    } else if (Head == pcb) {
        Head = pcb->next;
    // pcb is in the middle of the list
    } else {
        PCB *current = Head;
        while (current->next != pcb) {
            current = current->next;
        }
        current->next = pcb->next;
    }

    // move pcb to the end of the list
    pcb->next = NULL;

    // empty list
    if (Tail == NULL) {
        Head = pcb;
    } else {
        Tail->next = pcb;
    }
    Tail = pcb;
    */
}

void RR_Scheduling() {
    PCB *pCurr = Head;
    while (pCurr != NULL) {
        for(int i=0; i < 8; i++) {
            CPUreg[i] = pCurr->myReg[i]; // context switching
            CPUreg[i] = CPUreg[i] + 1;  // work done by cpu
            pCurr->myReg[i] = CPUreg[i];
        }
        if (pCurr->CPUburst <= quantum) {
            setPerformanceData(pCurr, quantum); //printf("\t\t\ttmp->CPUburst: %d\n",tmp->CPUburst);
            printf("Process %d is completed at %d ms\n", pCurr->ProcId, CLOCK);
            rmNodeList(pCurr, pCurr->ProcId);
        }
        else if (pCurr->CPUburst > quantum) {
            setPerformanceData(pCurr, quantum);
            printf("Process %d is completed at %d ms\n", pCurr->ProcId, CLOCK);
            if (pCurr->CPUburst > 0) {
                insertPCB(pCurr);
            }
            rmNodeList(pCurr, pCurr->ProcId);
        }
        pCurr = Head; // get next proc
    }
    printPerformanceData();
}
