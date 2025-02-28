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

void appendArguments(char **token, char* (*arguments)[2048])
{
  int i = 1;
  char* delim = " ";
  while (*token != NULL)
  {
    (*token)[strlen(*token)-1] = 0;
    (*arguments)[i] = (*token);
    i++;
    (*token) = strtok(0 , ARGS_DELIM);
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

/**
 * Checking whether a command is built-in or not
 * 
 * Returns
 * =======
 * 1 - If is built-in
 * 0 - If not
 */
int inspectBuiltInCommand(char* commandInput)
{
  return (strstr(commandInput, "exit") || strstr(commandInput, "path") || strstr(commandInput, "cd"));
}

void handleCommand(char* commandInput)
{
  // Preserving the command in its original form for comparisons
  char* originalCommand = strdup(commandInput);

  char *delim = " ";
  char *token = strtok(commandInput, delim);

  // Removing newline, provided no arguments were given
  handleNoArg(&token, originalCommand);

  char *coreCommand = checkBinDir(token);

  char *arguments[2048] = {};
  arguments[0] = token;

  // Getting the command together
  char command[5 + sizeof(token)] = "/bin/";
  strcat(command, token);
  token = strtok(0 , ARGS_DELIM);

  // Getting the arguments together
  appendArguments(&token, &arguments);

  // Creating a thread for the command 
  int pid; 
  int status;
  switch(fork())
  {
    case -1:
      write(STDERR_FILENO, error_message, strlen(error_message));
      break;
    case 0:
      childProcess(command, arguments);
      break;
    default:
      if (wait(&status) == -1)
      {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
      break;
  }
}

