/**
 * This file contains the linked list data structure
 */ 
struct node {
  char* line;
  struct node *next;
};

void freeLinkedList(struct node** root)
{
  struct node* current;
  while (*root != NULL)
  {
    current = *root;
    *root = (*root)->next;
    free(current->line);
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
}

void putTokensInLinkedList(struct node* conductor, char* buffer)
{
  char *token = strtok(buffer, CMD_DELIM);
  while (token != NULL)
  {
    removeNewLine(&token);
    conductor->line = strdup(token);
    if ((conductor->next = malloc(sizeof(struct node))) == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
    conductor = conductor->next;
    token = strtok(0, CMD_DELIM);
  }
  conductor->next = NULL;
}

