/**
 * strtok - https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
 * checking for EOF - https://stackoverflow.com/questions/64958306/recognizing-eof-vs-newline-in-getline-in-c
 */  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "modules/fileManip.c"

#define BUFFER_SIZE    1024
#define ERR_INPUTFILE  "Error when attempting to open the input file!\n"

int main(int argc, char** argv) 
{
  char error_message[30] = "An error has occurred\n";
  char* buffer;
  char* token;
  size_t bufferSize = BUFFER_SIZE;
  FILE* inputFile;
  char fileContentBuffer[BUFFER_SIZE];


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
    int i = 0;
    printf("wish> ");
    
    getline(&buffer, &bufferSize, inputFile);
    
    // Exiting with 0 if EOF is reached
    if (feof(inputFile))
    {
      exit(0);
    }

    // Going through all inputs (separated by space)
    char *token = strtok(buffer, " ");
    while (token != 0) 
    {
      if (i == 0 && strstr(token, "exit")) 
      {
        exit(0);
      }
      printf("%s\n", token);
      token = strtok(0, " ");
    }

    /*
    if (strstr(buffer, "exit"))
    {
      printf("bye");
      exit(0);
    }
    else if (strstr(buffer, "cd"))
    {
      printf("yo");
    }
    else if (strstr(buffer, "path"))
    {
      printf("hey");
    }
    else
    {
      printf("invalid input");
    }
    */
  }
}

