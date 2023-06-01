#include "debug.h"
#include <stdio.h>

// Print an array
void debug_print_array(double *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%f ", array[i]);
  }
  printf("\n");
}

// Print a half of an array
void debug_print_half_array(double *array, int begin, int end)
{
  for (int i = begin; i < end; i++)
  {
    printf("%f ", array[i]);
  }
  printf("\n");
}

// Print the sorted subarrays of the original array
// after the selection sort threads are done.
// It prints half of the array.
void debug_print_selection_sort_threads(double *arr, int begin1, int begin2, int SIZE)
{
  printf("t0 sorted array:\n\t");
  debug_print_half_array(arr, begin1, SIZE/2);
  printf("t1 sorted array:\n\t");
  debug_print_half_array(arr, begin2, SIZE);
}
