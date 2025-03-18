/**
 * Built-in command for exiting the program
 */
void commandExit(char* const* arguments)
{
  if (arguments[1] != NULL)
  {
    write(STDERR_FILENO, ERR_EXITARGS, strlen(ERR_EXITARGS));
    exit(1);
  }
  exit(0);
}

void commandCd(char* const* arguments)
{
  // Exiting with error if this is not met: 0 < args < 2
  if (arguments[1] == NULL || arguments[2] != NULL)
  {
    write(STDERR_FILENO, ERR_CDARGNUM, strlen(ERR_CDARGNUM));
    exit(1);
  }
  // Changing the directory and inspecting the results. Calling an error if it fails.
  if (chdir(arguments[1]) != 0)
  {
    write(STDERR_FILENO, ERR_CDFAIL, strlen(ERR_CDFAIL));
    exit(1);
  }
}

void commandPath(char* const* arguments, struct node** pathRoot)
{
  freeLinkedList(pathRoot);
  initializeRoot(pathRoot);
  
  if (arguments[1] == NULL)
  {
    return;
  }

  struct node* pathConductor = *pathRoot;
  pathConductor->line = strdup(arguments[1]);
  pathConductor->next = NULL;

  for (int i = 2 ; arguments[i] != NULL ; i++)
  {
    if ((pathConductor->next = malloc(sizeof(struct node))) == NULL)
    {
      write(STDERR_FILENO, ERR_MALLOC, strlen(ERR_MALLOC));
      exit(1);
    }  
    pathConductor = pathConductor->next;
    
    // Removing newline from the last argument
    if (arguments[i + 1] == NULL) 
    {
      char* string = strdup(arguments[i]);
      removeNewLine(&string);
      pathConductor->line = strdup(string);
      free(string);
      pathConductor->next = NULL;
      continue;
    }

    // The normal procedure for an argument
    pathConductor->line = strdup(arguments[i]);
    pathConductor->next = NULL;
  }
}
