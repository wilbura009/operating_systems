#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"

void printStudentName()
{
  printf("Student Name: wb\n");
}

void printInputFileName(char *s)
{
  printf("Input File Name: %s\n", s);
}

void printSchedulingAlg(char *s)
{
  printf("CPU Scheduling Alg: %s\n\n", s);
}

void printHeading(char *f, char *a)
{
  printStudentName();
  printInputFileName(f);
  printSchedulingAlg(a);
}

void printHelpMsg()
{
  printf("USAGE:\n ./prog -alg [FIFO|SJF|PR|RR] [-quantum integer(ms)] -input [input_file_name.txt]\n");
  exit(0);
}
