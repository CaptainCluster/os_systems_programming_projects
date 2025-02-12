#include <stdio.h>
#include <stdlib.h>

/**
 * The sources used for this repository are in the README.md file
 */ 

#define ERR_INPUTFILE  "Error when attempting to open the input file!\n"
#define ERR_OUTPUTFILE "Error when attempting to open the output file!\n"

struct node {
  char* line;
  struct node *next;
};

/**
 * One function to handle all file openings
 * Args
 * ====
 * 1) The file name
 * 2) Open method (read - "r", write "w", etc)
 * 3) Error message, in case the file opening fails
 */ 
FILE* openFile(char* fileName, char* openMethod, char* errorMessage)
{
  FILE* openedFile;
  if ((openedFile = fopen(fileName, openMethod)) == NULL)
  {
    fprintf(stderr, "%s", errorMessage);
    exit(1);
  }
  return openedFile;
}

int main(int argc, char** argv)
{
  FILE* inputFile;
  FILE* outputFile;
  struct node *root;
  struct node *conductor;

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
      inputFile  = openFile(argv[1], "r", ERR_INPUTFILE);
      outputFile = openFile(argv[2], "w", ERR_OUTPUTFILE);
      break;

    default:
      fprintf(stdout, "You should only pass two args max: an input file and an output file.\n");
      exit(0);
  }

  // Continuing with the defined files
  
  
  fclose(inputFile);
  fclose(outputFile);
  return 0;
}
