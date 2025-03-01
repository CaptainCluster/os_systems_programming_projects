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
  while ( conductor != NULL ) 
  {
    // Separating the potential multiple arguments
    conductor = conductor->next;
  }
}

void freeLinkedList(struct node** root)
{
  struct node* current;
  while (*root != NULL)
  {
    current = *root;
    *root = (*root)->next;
    free(current);
  }
}

void initializeRoot(struct node** root)
{
  if ((*root = malloc(sizeof(struct node))) == NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  if (((*root)->next = malloc(sizeof(struct node))) == NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }  
}

void putTokensInLinkedList(struct node* conductor, char* buffer)
{
  char *token = strtok(buffer, CMD_DELIM);
  while (token != NULL)
  {
    removeNewLine(&token);

    conductor->line = strdup(token);
    conductor = conductor->next;
    if ((conductor->next = malloc(sizeof(struct node))) == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
    token = strtok(0, CMD_DELIM);
  }
}

