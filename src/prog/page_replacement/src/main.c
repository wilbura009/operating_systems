#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "page_replacement-common.h"
#include "page_replacement-queue.h"

void msg_print_usage()
{
  printf("USAGE:   ./main <algorithm> <input_file> \n");
  printf("  OPTIONS: \n\n");
  printf("    -fifo:  FIFO page replacement algorithm \n");
  printf("    -lru:   LRU page replacement algorithm \n");
  printf("  EXAMPLE: \n");
  printf("    ./main -fifo input.txt \n");
}

int validate_arg_number(int argc)
{
  // If the number of arguments is not 3, print an error message and exit
  if (argc != 3)
  {
    printf("ERROR: Invalid number of arguments\n\n");
    msg_print_usage();
    return 1;
  }
  return 0;
}

int validate_algorithm_option(char** argv)
{
  if (strcmp(argv[1], "-fifo") != 0 &&
      strcmp(argv[1], "-lru")  != 0)
  {
    printf("ERROR: Invalid algorithm\n\n");
    msg_print_usage();
    return 1;
  }
  return 0;
}

char* read_input_file()
{
  // Open the input file for reading
  FILE* fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error: failed to open input file.\n");
    return NULL;
  }

  // Determine the size of the file
  fseek(fp, 0L, SEEK_END);
  int file_size = ftell(fp);
  rewind(fp);

  // Allocate memory for the input buffer
  char* input_buffer = (char*)malloc(file_size + 1);
  if (input_buffer == NULL)
  {
    printf("Error: failed to allocate memory for input buffer.\n");
    fclose(fp);
    return NULL;
  }

  // Read the contents of the file into the buffer
  int read_size = fread(input_buffer, sizeof(char), file_size, fp);
  if (read_size != file_size)
  {
    printf("Error: failed to read input file.\n");
    free(input_buffer);
    fclose(fp);
    return NULL;
  }

  // Add a null terminator to the end of the buffer
  input_buffer[file_size] = '\0';

  // Close the file
  fclose(fp);

  return input_buffer;
}

void print_page_references(int* page_references, int num_page_references)
{
  printf("Page references: ");
  for (int i = 0; i < num_page_references; i++)
  {
    printf("%d ", page_references[i]);
  }
  printf("\n");
}

int get_num_page_references(char* input_string)
{
  int num_page_references = 0;
  // Copy the input string so that we don't modify the original
  char* input_string_copy = (char*)malloc(strlen(input_string) + 1);
  strcpy(input_string_copy, input_string);

  char* token = strtok(input_string_copy, " "); // Get the first token
  while (token != NULL)
  {
    num_page_references++;
    token = strtok(NULL, " "); // Get the next token
  }
  free(input_string_copy);

  return num_page_references;
}

void print_num_page_references(int num_page_references)
{
  printf("Number of page references: %d\n", num_page_references);
}

int* get_page_references(char* input_string, int num_page_references)
{
  int* page_references = (int*)malloc(num_page_references * sizeof(int));
  memset(page_references, 0, num_page_references * sizeof(int)); // Init the array to 0

  // Copy the input string so that we don't modify the original
  char* input_string_copy = (char*)malloc(strlen(input_string) + 1);
  strcpy(input_string_copy, input_string);

  char* token = strtok(input_string_copy, " "); // Get the first token
  int i = 0;
  while (token != NULL)
  {
    page_references[i] = atoi(token);
    i++;
    token = strtok(NULL, " "); // Get the next token
  }
  free(input_string_copy);

  return page_references;
}

void fifo(int num_frames, int num_page_references, int* page_references)
{
  int num_page_faults = 0; // Page fault: not in memory
  int num_page_hits = 0;   // Page hit: in memory
  Queue* queue = queue_init();
  // TODO: check if queue is null

  // MEM LEAK HERE
  for (int i = 0; i < num_page_references; i++)
  {
    queue_add(queue, num_frames, page_references[i],
              &num_page_faults, &num_page_hits);
  }

  printf("\n");
  printf("Number of page faults: %d\n", num_page_faults);
  printf("Number of page hits: %d\n", num_page_hits);

  queue_free(queue);
}

void lru(int num_frames, int num_page_references, int* page_references)
{
  int num_page_faults = 0; // Page fault: not in memory
  int num_page_hits = 0;   // Page hit: in memory
  Queue* queue = queue_init();
  // TODO: check if queue is null

  for (int i = 0; i < num_page_references; i++)
  {
    printf("%d | ", page_references[i]);
    // If the page is in memory, move it to the back of the queue
    if (queue_has_page(queue, page_references[i]))
    {
      num_page_hits++;
      queue_remove_page(queue, page_references[i]);
      queue_append(queue, page_references[i]);
      queue_print(queue);
      printf("%7s\n", PAGE_HIT_MSG);
    }
    // Page is not in memory
    // - If the queue is full, remove the page from the front of the queue
    // - Add the page to the back of the queue
    else
    {
      num_page_faults++;
      if (queue_is_full(queue, num_frames))
        queue_remove_top(queue); // Remove the page from the front of the queue

      queue_append(queue, page_references[i]); // Add the page to the back of the queue
      queue_print(queue);

      // Check the queue size to determine the number of spaces to print
      // TODO: Calculate the number of spaces to print instead of hardcoding
      if (queue_is_full(queue, num_frames))
        printf("%7s\n", PAGE_FAULT_MSG);
      else
        if (queue_get_size(queue) == 1)
          printf("%11s\n", PAGE_FAULT_MSG);
        else
          printf("%9s\n", PAGE_FAULT_MSG);
    }
  }

  printf("\n");
  printf("Number of page faults: %d\n", num_page_faults);
  printf("Number of page hits: %d\n", num_page_hits);

  queue_free(queue);
}

int handle_algorithm_option(char** argv, int num_frames, int num_page_references, int* page_references)
{

  printf("==================== INPUT ===================\n\n");
  print_num_page_references(num_page_references);
  print_page_references(page_references, num_page_references);
  printf("\n");

  switch (argv[1][1])
  {
    case 'f':
      // -fifo case
      printf("==================== FIFO ====================\n\n");
      fifo(num_frames, num_page_references, page_references);
      break;
    case 'l':
      // -lru case
      printf("==================== LRU =====================\n\n");
      lru(num_frames, num_page_references, page_references);
      break;
    default:
      // invalid algorithm case
      printf("ERROR: Invalid algorithm\n\n");
      msg_print_usage();
      return 1;
  }
  return 0;
}


/**
 * Main function to test the queue implementation
 * USAGE:   ./main <algorithm> <input_file>
 *
 * EXAMPLES:
 *    ./main -fifo input.txt
 *    ./main -lru  input.txt
 *
 * NOTE: The input file should contain a single line of space-separated integers
 *      representing the page references. For example: 1 2 3 4 2 5 2 3 2 1 2 5 2 1
 */
int main(int argc, char** argv)
{

  if (validate_arg_number(argc) != 0)
    exit(1);

  if (validate_algorithm_option(argv) != 0)
    exit(1);

  char* input_string = NULL;
  input_string = read_input_file();
  if (input_string == NULL)
    exit(1);

  // TODO: This will come from user input
  int num_frames = 4; // Number of frames in memory
  int *page_references = NULL;
  int num_page_references = 0;

  num_page_references = get_num_page_references(input_string);
  page_references = get_page_references(input_string, num_page_references);

  // --------- NO MEMORY LEAKS TO HERE ---------

  if (handle_algorithm_option(argv, num_frames,num_page_references, page_references) != 0)
    exit(1);

  free(page_references);
  free(input_string);

  return 0;
}
