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
void traverseList(struct node* conductor)
{
  while ( conductor != 0 ) 
  {
    // Separating the potential multiple arguments
    fprintf(stdin , "%s", conductor->line );
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

void putCommandsInLinkedList(struct node* conductor, char* buffer)
{
  char *token = strtok(buffer, "&");
  while (token != 0)
  {
    conductor->line = strdup(token);
    conductor = conductor->next;
    if ((conductor->next = malloc(sizeof(struct node))) == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }  
    printf("%s\n", token);
    token = strtok(0, "&");
  }

}
