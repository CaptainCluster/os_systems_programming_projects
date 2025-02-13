/**
 * OS and Systems Programming course - Project 1
 * The sources used for this repository are in the README.md file
 *
 * While this is the main file for this program, I separated the 
 * project into other files to keep the code modular and clean.
 *
 * The other files
 * ===========
 * filemanip.c  - For addressing file-related concerns
 * linkedlist.c - The linked list data structure 
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/filemanip.c"
#include "modules/linkedlist.c"

#define ERR_INPUTFILE  "Error when attempting to open the input file!\n"
#define ERR_OUTPUTFILE "Error when attempting to open the output file!\n"
#define ERR_MALLOC     "malloc failed.\n"
#define ERR_MEMORY     "Out of memory!\n"
#define ERR_SAMEFILE   "The I/O files should not be the same!\n"
#define ERR_ARGS       "usage: reverse <input> <output>\n"
#define BUFFER_SIZE    256

int main(int argc, char** argv)
{
  FILE* inputFile;
  FILE* outputFile;
  struct node *root;
  struct node *conductor;
  char* buffer;
  size_t bufferSize = BUFFER_SIZE;

  /** 
   * Defining the input and output files for the program to operate with
   * case 1 - No I/O files passed
   * case 2 - Input file passed
   * case 3 - I/O files passed 
   * Default - More than 2 arguments passed
   */ 
  switch(argc)
  {
    case 1:
      inputFile  = stdin;
      outputFile = stdout;
      break;
    
    case 2:
      inputFile  = openFile(argv[1], "r", ERR_INPUTFILE);
      outputFile = stdout;
      break;

    case 3:
      if (!checkInputOutputValidity(argv[1], argv[2]))
      {
        fprintf(stderr, "%s", ERR_SAMEFILE);
        exit(1);
      }  
      inputFile  = openFile(argv[1], "r", ERR_INPUTFILE);
      outputFile = openFile(argv[2], "w", ERR_OUTPUTFILE);
      break;

    default:
      fprintf(stderr, "%s", ERR_ARGS);
      exit(1);
  }

  // Allocating memory for both the root of the linked list and the next node
  if ((root = malloc(sizeof(struct node))) == NULL)
  {
    fprintf(stderr, "%s", ERR_MALLOC);
    exit(1);
  }
  if ((root->next = malloc(sizeof(struct node))) == NULL)
  {
    fprintf(stderr, "%s", ERR_MALLOC);
    exit(1);
  }  

  conductor = root;
  if (conductor == 0)
  {
    fprintf(stderr, "%s", ERR_MEMORY);
    exit(1);
  }

  // Putting the input lines into a linked list
  while (1)
  {
    if ((buffer = (char*) malloc(BUFFER_SIZE * sizeof(char))) == NULL)
    {
      fprintf(stderr, "%s\n", ERR_MALLOC);
      exit(1);
    }
    if (getline(&buffer, &bufferSize, inputFile) <= 0)
    {
      break;
    }
    conductor->line = strdup(buffer);
    if ((conductor->next = malloc(sizeof(struct node))) == NULL)
    {
      fprintf(stderr, "%s", ERR_MEMORY);
      exit(1);
    }
    conductor = conductor->next;
  }

  if ((conductor->next = malloc(sizeof(struct node))) == NULL)
  {
    fprintf(stderr, "%s", ERR_MEMORY);
    exit(1);
  }
  conductor = conductor->next;
  conductor->next = 0;

  root = reverseLinkedList(root);
  conductor = root;
  
  while ( conductor != 0 ) 
  {
    fprintf(outputFile, "%s", conductor->line );
    conductor = conductor->next;
  }

  fclose(inputFile);
  fclose(outputFile);
  return 0;
}
