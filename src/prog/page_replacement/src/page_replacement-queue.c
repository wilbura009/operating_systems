#include <stdio.h>
#include <stdlib.h>

#include "page_replacement-common.h"
#include "page_replacement-queue.h"

Queue* queue_init()
{
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

void queue_free(Queue* queue)
{
  Node* temp = queue->front;
  while (temp != NULL) {
    Node* next = temp->next;
    free(temp);
    temp = next;
  }
  free(queue);
}

void queue_remove_top(Queue* queue)
{
  if (queue->front == NULL) {
    printf("Queue is empty\n");
    return;
  }
  Node* temp = queue->front;
  queue->front = queue->front->next;

  if (queue->front == NULL)
    queue->rear = NULL;

  free(temp);
}

void queue_remove_page(Queue* queue, int page)
{
  Node* temp = queue->front;
  Node* prev = NULL;
  while (temp != NULL) {
    if (temp->data == page)
    {
      if (prev == NULL)
      {
        queue->front = temp->next;
      }
      else
      {
        prev->next = temp->next;
      }
      free(temp);
      return;
    }
    prev = temp;
    temp = temp->next;
  }
}

int queue_remove_at_index(Queue *queue, int index)
{
  Node* temp = queue->front;
  Node* prev = NULL;
  int count = 0;
  while (temp != NULL) {
    if (count == index)
    {
      if (prev == NULL)
      {
        queue->front = temp->next;
      }
      else
      {
        prev->next = temp->next;
      }
      free(temp);
      return 1;
    }
    prev = temp;
    temp = temp->next;
    count++;
  }
  return 0;
}

int queue_get_num_pages(Queue* queue)
{
  Node* temp = queue->front;
  int count = 0;
  while (temp != NULL) {
    count++;
    temp = temp->next;
  }
  return count;
}

int queue_has_page(Queue* queue, int page)
{
  Node* temp = queue->front;
  while (temp != NULL) {
    if (temp->data == page)
    {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

// Finds the optimal page to replace, return its index
int queue_find_opt_page(Queue* queue, int* page_references, int num_page_references, int current_index)
{
  int optimal_page_index = -1;
  int optimal_page_index_value = -1;
  Node* temp = queue->front;
  while (temp != NULL) {
    int page = temp->data;
    int page_index = -1;
    for (int i = current_index; i < num_page_references; i++)
    {
      if (page_references[i] == page)
      {
        page_index = i;
        break;
      }
    }
    if (page_index > optimal_page_index_value)
    {
      optimal_page_index_value = page_index;
      optimal_page_index = page;
    }
    temp = temp->next;
  }
  return optimal_page_index;
}

int queue_is_full(Queue* queue, int num_frames)
{
  return queue_get_num_pages(queue) == num_frames;
}

int queue_get_size(Queue* queue)
{
  Node* temp = queue->front;
  int count = 0;
  while (temp != NULL) {
    count++;
    temp = temp->next;
  }
  return count;
}

void queue_add(Queue* queue, int num_frames, int data, int* page_faults, int* page_hits)
{
  Node* temp = NULL;
  temp = new_node(data);

  printf("%d | ", data);

  // If the queue is empty, then the new node is front and rear both
  if (queue->rear == NULL)
  {
    queue->front = temp;
    queue->rear = temp;
    (*page_faults)++;
    queue_print(queue);
    printf("%10s\n", PAGE_FAULT_MSG);
    return;
  }

  // Check if the queue is full by the number of frames
  if (queue_is_full(queue, num_frames))
  {
    // Check if the page is already in the queue.
    // If it is, then it is a page hit and we do not need to add it to the queue
    if (queue_has_page(queue, data))
    {
      (*page_hits)++;
      queue_print(queue);
      printf("%6s\n", PAGE_HIT_MSG);
      return;
    }
    queue_remove_top(queue);
  }

  // --- MEM LEAK HERE ---

  // Add the new node at the end of queue and change rear to the new node
  queue->rear->next = temp;
  queue->rear = temp;
  (*page_faults)++; // Increment the page fault counter
  queue_print(queue);

  // Check the queue size to determine the number of spaces to print
  if (queue_is_full(queue, num_frames))
    printf("%6s\n", PAGE_FAULT_MSG);
  else
    printf("%8s\n", PAGE_FAULT_MSG);

}

void queue_append(Queue *queue, int data)
{
  Node* temp = NULL;
  temp = new_node(data);

  // If the queue is empty, then the new node is front and rear both
  if (queue->rear == NULL)
  {
    queue->front = temp;
    queue->rear = temp;
    return;
  }

  // Add the new node at the end of queue and change rear to the new node
  queue->rear->next = temp;
  queue->rear = temp;
}

int queue_insert_at_index(Queue* queue, int index, int data)
{
  Node* temp = NULL;
  temp = new_node(data);

  // If the queue is empty, return 1 to indicate an error
  if (queue->rear == NULL)
    return 1;

  // If the index is 0, return 1 to indicate an error
  if (index == 0)
    return 1;

  // If the index is greater than the size of the queue, return 1 to indicate an error
  if (index > queue_get_size(queue))
    return 1;

  // Otherwise, we need to insert the node at the specified index
  Node* prev = NULL;
  Node* curr = queue->front;
  int count = 0;
  while (curr != NULL) {
    if (count == index)
    {
      prev->next = temp;
      temp->next = curr;
      return 0; // Success 
    }
    prev = curr;
    curr = curr->next;
    count++;
  }
  return 1; // Error
}

void queue_print(Queue* queue)
{
  Node* temp = queue->front;
  while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
}
