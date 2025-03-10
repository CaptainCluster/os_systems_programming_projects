#include <stdio.h>
void buildInCommands(char* const* arguments, struct node** pathRoot)
{
  if (strstr(arguments[0], "exit")) 
  {
    commandExit(arguments);
  }
  else if(strstr(arguments[0], "cd"))
  {
    commandCd(arguments);
  }
  else if (strstr(arguments[0], "path"))
  {
    commandPath(arguments, pathRoot);
  }
}

void appendArguments(char **token, char* (*arguments)[2048], int isBuiltIn)
{
  int i = 1;
  while (*token != NULL)
  {
    removeNewLine(token);
    (*arguments)[i] = (*token);
    (*token) = strtok(0 , ARGS_DELIM);
    i++;
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
char* checkBinDir(char* command, struct node* conductor) 
{
  char* path;
  
  while (conductor != NULL)
  {
    // Allocating memory based on the given command and a path entry in the linked list
    if((path = (char*) malloc(strlen(command) + strlen(conductor->line) + 1)) == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
    strcpy(path, conductor->line);
    strcat(path, command);

    // Ensuring the path file can be accessed
    if (access(path, X_OK) != -1)
    {
      return path;
    }

    // Can't access? Freeing up allocated memory and traversing the list.
    free(path);
    conductor = conductor->next;
  }
  // The error that triggers if no accessible, and adequate, path is found
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

/**
 * The core function for handling each of the input commands
 */
void handleCommand(char* commandInput, struct node** pathRoot)
{
  struct node* pathConductor = *pathRoot;

  // Preserving the command in its original form for comparisons
  char *token = strtok(commandInput, ARGS_DELIM);

  // Removing newline, provided no arguments were given
  char *arguments[2048] = {};
  arguments[0] = token;

  if (inspectBuiltInCommand(token))
  {
    token = strtok(0 , ARGS_DELIM);
    appendArguments(&token, &arguments, 1);
    buildInCommands(arguments, pathRoot);
    return;
  }

  // Fetching the command in the following format: <path>/<command>
  // For instance: /bin/ls
  char *command = checkBinDir(token, pathConductor);
  token = strtok(0 , ARGS_DELIM);

  // Getting the arguments together
  appendArguments(&token, &arguments, 0);

  /**
   * The shell command will run in a child process.
   * 
   * Child process
   * =============
   * 1) Checks whether the output has to be redirected into a file
   * 2) Executes the command, with its arguments in mind
   *
   * Parent process
   * ==============
   * Frees the memory allocation for the command variable.
   */
  int status;
  switch(fork())
  {
    case -1:
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
      break;
    case 0:
      openRedirect(&arguments);
      execv(command, arguments);
      break;
    default:
      if (wait(&status) == -1)
      {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
      free(command);
      break;
  }
}

