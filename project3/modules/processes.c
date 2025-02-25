#include <string.h>
void handleCommand(char* commandInput)
{
  char *delim = " ";
  char *token = strtok(commandInput, delim);
 
  // An index to determine whether an input is a command or an arg
  int i = 0;
  int j = 0;

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
  char arguments[2048];

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

  // Not a valid command? Returning
  if (i == 0 && !(strstr(token, "cd") || strstr(token, "path")))
  {
    return;
  }

  // Getting the arguments together

  // Creating a thread for the command 
  int pid; 
  int status;
  switch(pid = fork())
  {
    case -1:
      write(STDERR_FILENO, error_message, strlen(error_message));
      break;
    case 0:
      execv("/bin/ls", NULL);
      break;
    case 1:
      if (wait(&status) == -1)
      {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
      printf("Hi");
      break;
  }
}
