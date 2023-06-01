#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "errExit.h"
#include "debug.h"

// Global variables
int SIZE;
int begin1, begin2;
double *arr, *temp;
struct timespec ts_begin, ts_end;
double elapsed;  

// Print the usage of the program
void print_help()
{
  printf("Usage: ./main arg1\n\n");
}

// Validate that the user entered an arg1
void validate_args(int argc)
{
  if (argc != 2)
  {
    print_help();
    errExit("validate_args(): Invalid number of arguments");
  }
}

// Return a random number between 0 and 1000
int get_random_number()
{
  return rand() % 1000;
}

// Populate an array with random numbers
void set_array(double *array, int size)
{
  for (int i = 0; i < size; i++)
    array[i] = get_random_number();
}

// Thread function for selection sort
void *selection_sort_thread(void *arg)
{
  int begin = *(int *)arg;
  int end = begin + SIZE/2; // end is the index of the last element
                            // in the subarray
  int i, j, min;
  double tmp; // Temporary variable for swapping

  for (i = begin; i < end - 1; ++i)
  {
    min = i;
    // Find the minimum value in the unsorted subarray
    for (j = i + 1; j < end; ++j)
    {
      if (arr[j] < arr[min])
        min = j;
    }
    // Swap the values of arr[i] and arr[min]
    tmp = arr[min];
    arr[min] = arr[i];
    arr[i] = tmp;
  }
  pthread_exit(NULL);
}

// Non-thread function for selection sort
void selection_sort(int beg)
{
  int begin = beg;
  int end = begin + SIZE/2; // end is the index of the last element
                            // in the subarray
  int i, j, min;
  double tmp; // Temporary variable for swapping

  for (i = begin; i < end - 1; ++i)
  {
    min = i;
    // Find the minimum value in the unsorted subarray
    for (j = i + 1; j < end; ++j)
    {
      if (arr[j] < arr[min])
        min = j;
    }
    // Swap the values of arr[i] and arr[min]
    tmp = arr[min];
    arr[min] = arr[i];
    arr[i] = tmp;
  }
}

void start_clock()
{
  clock_gettime(CLOCK_MONOTONIC, &ts_begin);
}

void end_clock()
{
  clock_gettime(CLOCK_MONOTONIC, &ts_end);
  elapsed = (ts_end.tv_sec - ts_begin.tv_sec) * 1000.0; // Convert seconds to milliseconds
  elapsed += (ts_end.tv_nsec - ts_begin.tv_nsec) / 1000000.0; // Convert nanoseconds to milliseconds
}

void *merge_sort_thread(void *arg)
{
  int mid = SIZE/2;
  int i = 0;
  int j = mid;
  int k = 0;

  // merge two sorted arrays
  while (i < mid && j < SIZE)
  {
    // copy smaller element from left array to temp array
    if (arr[i] < arr[j])
      temp[k++] = arr[i++];

    // copy smaller element from right array to temp array
    else
      temp[k++] = arr[j++];
  }
  // copy remaining elements from left array
  while (i < mid)
    temp[k++] = arr[i++];

  // copy remaining elements from right array
  while (j < SIZE)
    temp[k++] = arr[j++];

  // copy sorted values from temp array to original array
  for (i = 0; i < SIZE; i++)
    arr[i] = temp[i];

  pthread_exit(NULL);
}

void merge_sort()
{
  int mid = SIZE/2;
  int i = 0;   // index of left subarray
  int j = mid; // index of right subarray
  int k = 0;   // index of temp array

  // merge two sorted arrays
  while (i < mid && j < SIZE) {
    // copy smaller element from left array to temp array
    if (arr[i] < arr[j]) {
      temp[k++] = arr[i++];
      // copy smaller element from right array to temp array
    } else {
      temp[k++] = arr[j++];
    }
  }
  // copy remaining elements from left array
  while (i < mid) {
    temp[k++] = arr[i++];
  }
  // copy remaining elements from right array
  while (j < SIZE) {
    temp[k++] = arr[j++];
  }
  // copy sorted values from temp array to original array
  for (i = 0; i < SIZE; i++) {
    arr[i] = temp[i];
  }
}

void debug_print_unsorted_array()
{
  printf("Unsorted array:\n\t");
  debug_print_array(arr, SIZE);
}

// Initialize the arrays and populate them with random numbers.
// This function is called before each sorting algorithm.
// Check if the arrays are not NULL before freeing them.
// This fuction may exit if malloc fails.
void init_arrays()
{
  if (arr != NULL)
    free(arr);

  if (temp != NULL)
    free(temp);

  arr = NULL, temp = NULL;

  // Use arg1 to malloc an int array of size arg1
  arr = malloc(SIZE * sizeof(double));
  temp = malloc(SIZE * sizeof(double));

  // Check if malloc failed
  if (arr == NULL || temp == NULL)
    errExit("init_arrays(): malloc");

  // Populate the array with random numbers
  set_array(arr, SIZE);
}

int main(int argc, char **argv) 
{ 
  validate_args(argc); // may exit here

  // Get arg 1 from user
  SIZE = atoi(argv[1]);

  begin1 = 0, begin2 = SIZE/2; // begin1 and begin2 are the
                               // starting index for each thread.
  pthread_t tids[3]; // 3 threads

  // Set to NULL to avoid and so that init_arrays()
  // can free them if they are not NULL.
  arr = NULL, temp = NULL;

  init_arrays();
  //debug_print_unsorted_array();

  // ------------------------------  Start clock: MULTI-THREAD  ------------------------------
  start_clock();

  // Create sorting threads for subarrays.
  // t0 sorts the first half of the array: arr[0] to arr[SIZE/2].
  if (pthread_create(&tids[0], NULL, selection_sort_thread, &begin1) != 0)
    errExit("t0");

  // t1 sorts the second half of the array: arr[SIZE/2] to arr[SIZE].
  if (pthread_create(&tids[1], NULL, selection_sort_thread, &begin2) != 0)
    errExit("t1");

  // Wait for threads to finish
  if (pthread_join(tids[0], NULL) != 0)
    errExit("t0");

  if (pthread_join(tids[1], NULL) != 0)
    errExit("t1");

  //debug_print_selection_sort_threads(arr, begin1, begin2, SIZE); // Print each thread's sorted array

  // Create merge thread
  if (pthread_create(&tids[2], NULL, merge_sort_thread, NULL) != 0)
    errExit("t2");

  // Wait for merge thread to finish
  if (pthread_join(tids[2], NULL) != 0)
    errExit("t2");

  // End clock
  end_clock();
  printf("Sorting is done in %fms when two threads are used.\n", elapsed);

  // --- Setup for single-threaded sorting ---
  init_arrays();
  //debug_print_unsorted_array();

  // ------------------------------  Start clock: SINGLE-THREAD  ------------------------------
  // Start clock
  clock_gettime(CLOCK_MONOTONIC, &ts_begin);
  start_clock();

  // Sort the first half of the array
  selection_sort(begin1);
  // Sort the second half of the array
  selection_sort(begin2);
  // Merge the two sorted subarrays
  merge_sort();

  // End clock
  end_clock();
  printf("Sorting is done in %fms when one thread is used.\n", elapsed);

  // Free memory
  free(arr);
  free(temp);

  return EXIT_SUCCESS; 
} 
