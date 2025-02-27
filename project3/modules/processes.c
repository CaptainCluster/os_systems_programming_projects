#include <stdlib.h>
#include <string.h>
void handleCommand(char* commandInput)
{
  char *delim = " ";
  char *token = strtok(commandInput, delim);
  char *arguments[2048] = {};
  arguments[0] = token;
  int i = 1;

  // Storing the main command into its own variable
  char *commandEnd;
  if ((commandEnd = (char*)malloc(sizeof(token))) == NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }

  // Getting the command together
  strcpy(commandEnd, token);
  char *command;
  command = (char*)malloc(sizeof("/bin/") + sizeof(commandEnd));
  strcat(command, "/bin/");
  strcat(command, commandEnd);


  // Inspecting for exit command. Exiting if it is provided. In case 
  // unnecessary arguments were given, the exit happens with an error.
  if (strstr(token, "exit")) 
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
  if (!(strstr(token, "cd") || strstr(token, "path")))
  {
    return;
  }

  token = strtok(0 , delim);
  // Getting the arguments together
  while (token != NULL)
  {
    token[strlen(token)-1] = 0;
    arguments[i] = token;
    i++;
    token = strtok(0 , delim);
  }
  arguments[i++] = NULL;

  // Creating a thread for the command 
  int pid; 
  int status;
  switch(pid = fork())
  {
    case -1:
      write(STDERR_FILENO, error_message, strlen(error_message));
      break;
    case 0:
      execv(command, arguments);
      break;
    case 1:
      if (wait(&status) == -1)
      {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
      break;
  }
}
