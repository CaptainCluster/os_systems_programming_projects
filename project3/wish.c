/**
 * strtok - https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
 * checking for EOF - https://stackoverflow.com/questions/64958306/recognizing-eof-vs-newline-in-getline-in-c
 * Creations of child processes - https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf
 */  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "const.c"
#include "modules/fileManip.c"
#include "modules/linkedlist.c"
#include "modules/printUtils.c"

#define BUFFER_SIZE    1024
#define ERR_INPUTFILE  "Error when attempting to open the input file!\n"

int main(int argc, char** argv) 
{
  char* buffer;
  char* token;
  size_t bufferSize = BUFFER_SIZE;
  FILE* inputFile;
  char fileContentBuffer[BUFFER_SIZE];
  struct node *root;
  struct node *conductor;

  //Checking whether the user has given an input file as a command-line arg
  switch(argc)
  {
    case 1:
      inputFile = stdin;
      break;
    default:
      inputFile = openFile(argv[1], "r", ERR_INPUTFILE);
      break;
  }

  // Initializing the linked list and conductor (current node)
  initializeRoot(root);
  conductor = root;
  if (conductor == 0)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }

  while (1) 
  {
    int i = 0;
    printPrompt(argc);  
    
    // Fetching the next line and ensuring it is not EOF
    getline(&buffer, &bufferSize, inputFile);
    checkEOF(inputFile);

    // Going through all inputs (separated by space)
    char *token = strtok(buffer, " ");
    while (token != 0) 
    {
      if (i == 0 && strstr(token, "exit")) 
      {
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
}

