/**
 * This file contains the linked list data structure
 */ 
struct node {
  char* line;
  struct node *next;
};

/**
 * Reversing the linked list. This is used before
 * traversing the list and writing into the
 * defined output.
 *
 * Returns
 * =======
 * New root for the linked list
 */ 
struct node* reverseLinkedList(struct node* root)
{
  struct node *conductor = root;
  struct node *previous = NULL;
  struct node *next;
  
  while (conductor->next->next != 0 && conductor != NULL) 
  {
    next = conductor->next;
    conductor->next = previous;
    previous = conductor;
    conductor = next;
  }
  return previous;
}

/**
 * Traversing the linked list and writing each line into the 
 * defined output file.
 */
void traverseListOutput(struct node* conductor, FILE* outputFile)
{
  while ( conductor != 0 ) 
  {
    fprintf(outputFile, "%s", conductor->line );
    conductor = conductor->next;
  }
}
