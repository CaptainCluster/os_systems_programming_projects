/**
 * strtok - https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
 * checking for EOF - https://stackoverflow.com/questions/64958306/recognizing-eof-vs-newline-in-getline-in-c
 * Creations of child processes - https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf
 * Using exec commands - https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
 * Appending data to array - https://stackoverflow.com/questions/26208788/can-someone-explain-how-to-append-an-element-to-an-array-in-c-programming
 * Removing newline from an arg - https://stackoverflow.com/questions/9628637/how-can-i-get-rid-of-n-from-string-in-c
 * More info about access - https://www.geeksforgeeks.org/access-command-in-linux-with-examples/
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
#include "modules/builtCommands.c"
#include "modules/processes.c"

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

  while (1) 
  {
    // Initializing the linked list and conductor (current node)
    initializeRoot(&root);
    conductor = root;
    if (conductor == 0)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }

    buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
    printPrompt(argc);

    // Fetching the next line and ensuring it is not EOF.
    getline(&buffer, &bufferSize, inputFile);
    checkEOF(inputFile);

    // Putting the separate commands into linked list
    putCommandsInLinkedList(conductor, buffer);

    // Traversing through the linked list in order to execute 
    // the commands in differing child processes.
    conductor = root;

    while ( conductor->next->next != 0 ) 
    {
      // Separating the potential multiple arguments
      handleCommand(conductor->line);
      conductor = conductor->next;
    }
  }
  // Freeing up the linked list and closing the input file
  freeLinkedList(&root);
  fclose(inputFile);
}

