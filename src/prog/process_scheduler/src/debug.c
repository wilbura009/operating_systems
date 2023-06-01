#include <stdio.h>
#include "pcb.h"

// Print the list
void printList(PCB *Head) {
    PCB *ptr = Head;
    printf("\n[ptr] == [head]");
    //start from the beginning
    while(ptr != NULL) {        
        printf(" -> ");
        printf("PCB: %p {\n", ptr);
        printf("\t\t\tProcID: %d\n",ptr->ProcId);
        printf("\t\t\tProcPR:  %d\n",ptr->ProcPR);
        printf("\t\t\tCPUburst: %d\n",ptr->CPUburst);
        printf("\t\t\tmyReg: ");
        for(int k=0; k < 8; k++) printf("%d", ptr->myReg[k]);
        printf("\n} [ptr]");
        ptr = ptr->next;
    }
    printf(" -> ");
    printf("[null]\n\n");
}

void printNode(PCB *ptr){
    printf("PCB: %p {\n", ptr);
    printf("\tProcID: %d\n",ptr->ProcId);
    printf("\tProcPR:  %d\n",ptr->ProcPR);
    printf("\tCPUburst: %d\n",ptr->CPUburst);
    printf("\tmyReg: ");
    for(int k=0; k < 8; k++) printf("%d", ptr->myReg[k]);
    printf("\n}\n");
}
