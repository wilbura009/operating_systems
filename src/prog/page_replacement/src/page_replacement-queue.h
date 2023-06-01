#ifndef PAGE_REPLACEMENT_QUEUE_H
#define PAGE_REPLACEMENT_QUEUE_H

#include "page_replacement-common.h"

// Defines the structure of the queue
typedef struct Queue Queue;
struct Queue {
  Node* front;
  Node* rear;
};

/****************************** INIT/UN-INIT ******************************/ 

// Initialize a new queue
Queue* queue_init();

// Frees the memory allocated to the queue
void queue_free(Queue* queue);

/****************************** NODE ADD/REMOVE ******************************/ 

// Adds an element to the back of the queue
// TODO: Rewrite this function - queue_append will replace this function 
void queue_add(Queue* queue, int num_frames, int data, int* page_faults, int* page_hits);

// Appends an element to the back of the queue
void queue_append(Queue* queue, int data);

// Removes an element from the top of the queue
void queue_remove_top(Queue* queue);

// Remove a specified page from the queue
void queue_remove_page(Queue* queue, int page);

// Remove an element at the specified index
int queue_remove_at_index(Queue* queue, int index);

/****************************** GET INFORMATION ******************************/ 

// Gets the number of elements in the queue
int queue_get_num_pages(Queue* queue);

// Checks if the queue has a page
int queue_has_page(Queue* queue, int page);

// Checks if the queue is full
int queue_is_full(Queue* queue, int num_frames);

// Returns the size of the queue
int queue_get_size(Queue* queue);

// Inserts an element at the specified index
int queue_insert_at_index(Queue* queue, int index, int data);

/****************************** PRINTING ******************************/ 

// Prints the elements of the queue
void queue_print(Queue* queue);

#endif // PAGE_REPLACEMENT_QUEUE_H
