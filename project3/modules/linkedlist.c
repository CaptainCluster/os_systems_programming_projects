/**
 * This file contains the linked list data structure
 */ 
struct node {
  char* line;
  struct node *next;
};

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

void freeLinkedList(struct node* root)
{
  struct node* current;
  while (root != NULL)
  {
    current = root;
    root = root->next;
    free(current);
  }
}

void initializeRoot(struct node* root)
{
  if ((root = malloc(sizeof(struct node))) == NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  if ((root->next = malloc(sizeof(struct node))) == NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }  
}
