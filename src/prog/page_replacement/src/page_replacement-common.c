#include <stdlib.h>
#include <stdio.h>

#include "page_replacement-common.h"

// Function to create a new node with the given data
Node* new_node(int data)
{
  Node* temp = (Node*)malloc(sizeof(Node));
  temp->data = data;
  temp->next = NULL;
  return temp;
}
