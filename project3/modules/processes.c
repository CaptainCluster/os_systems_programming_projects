void handleCommand(char* commandInput)
{
  char *token = strtok(commandInput, " ");
  int i = 0;
  while (token != 0) 
  {
    if (i == 0 && strstr(token, "exit")) 
    {
      // If additional args were passed to exit, an error is shown
      if ((token = (strtok(0, " "))) != 0)
      {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
      exit(0);
    }

    // Creating child process, but only with a valid command
    if (i == 0 && !(strstr(token, "cd") || strstr(token,"path")))
    {
      token = strtok(0, " ");
      continue; 
    }

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
        wait(NULL);
        break;
    }
    token = strtok(0, " ");
    printf("%s\n", token);
  }

}
