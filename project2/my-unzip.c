/**
 * fread - https://www.geeksforgeeks.org/fread-function-in-c/
 */ 

#include <stdio.h>
#include <stdlib.h>

#define ERR_ARGS "my-zip: file1 [file2 ...]"
#define ERR_FILE "Failed to open file."

/**
 * This function takes a zipped file and reads through the 4-byte
 * int values. The unzipping process continues as long as there 
 * are such entries that have not been gone through. After an int
 * entry has been found, the 1-byte character it is tied with is 
 * read. The int determines how many times the char is printed 
 * to standard output.
 */
void unZipProcess(FILE* inputFile)
{
  char *character;
  int numBuffer;
  while (fread(&numBuffer, 4, 1, inputFile) > 0)
  {
    fread(character, sizeof(char), 1, inputFile);

    // Printing the characters based on the amount before zipping
    for (int i = 0 ; i < numBuffer ; i++)
    {
      printf("%c", *character);
    }
  }
}

int main(int argc, char** argv)
{
  FILE* fp;

  /**
   * A switch case that manages scenarios based on given args
   *
   * Scenarios
   * =========
   * 1) No args given. Results in an error.
   * 2) >= 1 args. Attempts Attempts to open each arg as a file
   */ 
  switch(argc)
  {
    case 1:
      fprintf(stderr, "%s", ERR_ARGS);
      exit(1);
    default:
      for (int i = 1 ; i < argc ; i++)
      {
        if ((fp = fopen(argv[i], "r")) == NULL)
        {
          fprintf(stderr, "Failed to open file: '%s'\n", argv[i]);
          exit(1);
        }
        unZipProcess(fp);
      }
      break;
  }
  return 0;
}
