/**
 * This file contains the linked list data structure
 */ 
struct node 
{
  char* line;
  struct node *next;
};

/**
 * Frees up the lines stored in each node of the linked list.
 */
void freeLinkedList(struct node** root)
{
  struct node* conductor;
  while (*root != NULL)
  {
    conductor = *root;
    *root = (*root)->next;
    free(conductor->line);
    free(conductor);
  }
}

/**
 * Initialized the root of a linked list. This is usually 
 * used either when starting the program or when a linked 
 * list should be reinitialized after wiping off old data. 
 */
void initializeRoot(struct node** root)
{
  if ((*root = malloc(sizeof(struct node))) == NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  (*root)->line = NULL; 
  (*root)->next = NULL;
}

/**
 * Uses a specific delimeter to separate the buffer into tokens.
 * Every token is stored in its own entry in a linked list.
 */
void putTokensInLinkedList(struct node* conductor, char* buffer)
{
  char *token = strtok(buffer, CMD_DELIM);
  while (token != NULL)
  {
    removeNewLine(&token);
    conductor->line = strdup(token);
    token = strtok(0, CMD_DELIM);
    if (token == NULL)
    {
      break;
    }
    if ((conductor->next = malloc(sizeof(struct node))) == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
    conductor = conductor->next;
  }
  conductor->next = NULL;
}

