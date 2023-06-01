#ifndef PAGE_REPLACEMENT_COMMON_H
#define PAGE_REPLACEMENT_COMMON_H

#define PAGE_FAULT_MSG "| T |"
#define PAGE_HIT_MSG   "|   |"

// Define the structure of a node in the linked list
typedef struct Node Node;

struct Node
{
  int data;
  Node* next;
};

// Function to create a new node with the given data
Node* new_node(int data);

#endif // PAGE_REPLACEMENT_COMMON_H
