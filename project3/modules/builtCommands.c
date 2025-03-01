/**
 * Built-in command for exiting the program
 */
void commandExit(char* const* arguments)
{
  if (arguments[1] != NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  exit(0);
}

void commandCd(char* const* arguments)
{
  // Exiting with error if this is not met: 0 < args < 2
  if (arguments[1] == NULL || arguments[2] != NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  if (chdir(arguments[1]) != 0)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
}

void commandPath(char* const* arguments, struct node* pathConductor)
{
  int i;

  pathConductor->line = strdup(arguments[1]);
  pathConductor->next = NULL;

  for (i = 2 ; arguments[i] != NULL ; i++)
  {
    if ((pathConductor->next = malloc(sizeof(struct node))) == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }  
    pathConductor = pathConductor->next;
    
    // Removing newline from the last argument
    if (arguments[i + 1] == NULL) 
    {
      char* string = strdup(arguments[i]);
      string[strlen(string)-1] = 0;
      pathConductor->line = strdup(string);
      pathConductor->next = NULL;
      continue;
    }

    // The normal procedure for an argument
    pathConductor->line = strdup(arguments[i]);
    pathConductor->next = NULL;
  }
}
