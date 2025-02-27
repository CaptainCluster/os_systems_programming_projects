#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void childProcess(char* command, char* const* arguments)
{
  if (strstr(arguments[0], "exit")) 
  {
    // If additional args were passed to exit, an error is shown
    if (arguments[1] != NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
    exit(0);
  }
  
  execv(command, arguments);
}

/**
 * Ensures commands with no arguments can be executed properly
 * 
 * Current procedures
 * ==================
 * 1) Removal of newline
 */
void handleNoArg(char** token, char* originalCommand)
{
  if (strstr(*token, originalCommand))
  {
    (*token)[strlen(*token)-1] = 0;
  }
}

/**
 * Finding the right directory for the command, and whether the process has 
 * execute permission over it.
 *
 * Returns
 * =======
 * 1) Path of the dir with the execute permission
 * 2) If 1 does not occur, an error occurs
 */
char* checkBinDir(char* command) 
{
  char binPrimary[5 + sizeof(command)] = "/bin/";
  char binSecondary[9 + sizeof(command)] = "/usr/bin/";
  
  strcat(binPrimary, command);
  if (access(binPrimary, X_OK) != -1)
  {
    return strdup(binPrimary);
  }
  strcat(binSecondary, command);
  if (access(binSecondary, X_OK) != -1)
  {
    return strdup(binSecondary);
  }
  write(STDERR_FILENO, error_message, strlen(error_message));
  exit(1);
}

void handleCommand(char* commandInput)
{
  char* originalCommand = strdup(commandInput);

  char *delim = " ";
  char *token = strtok(commandInput, delim);

  handleNoArg(&token, originalCommand);

  char *coreCommand = checkBinDir(token);

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

  // Not a valid command? Returning
  if (!(strstr(token, "cd") || strstr(token, "path") || strstr(token, "ls") || strstr(token, "exit")))
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
      childProcess(command, arguments);
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

