void handleCommand(char* commandInput)
{
  char *delim = " ";
  char *token = strtok(commandInput, delim);
 
  // An index to determine whether an input is a command or an arg
  int i = 0;

  /**
   * Traversing through the input and its arguments
   * i = 0 -> A command
   * i > 0 -> An argument of the command
   *
   * Blocking the use of fork if the given command is not one 
   * of the following:
   * 1) path
   * 2) cd
   */  
  while (token != 0) 
  {
    printf("turn %d - %s\n", i, token);
    i = i + 1;
    
    // Inspecting for exit command. Exiting if it is provided. In case 
    // unnecessary arguments were given, the exit happens with an error.
    if (i == 0 && strstr(token, "exit")) 
    {
      // If additional args were passed to exit, an error is shown
      if ((token = (strtok(0, delim))) != 0)
      {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
      exit(0);
    }

    // Creating child process, but only with a valid command
    if (i == 0 && !(strstr(token, "cd") || strstr(token, "path")))
    {
      token = strtok(0, delim);
      i++;
      continue; 
    }

    /*
    int rc = fork();
    switch(rc)
    {
      case -1:
        write(STDERR_FILENO, error_message, strlen(error_message));
        break;
      case 0:
        printf("%s", token);
        break;
      case 1:
        printf("Hi");
        break;
    }
    */
    token = strtok(0, delim);
    //printf("%s\n", token);
  }
}
