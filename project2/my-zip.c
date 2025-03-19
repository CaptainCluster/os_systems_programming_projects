/**
 * fgetc  - https://www.geeksforgeeks.org/fgetc-fputc-c/
 * fwrite - https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm 
 * EOF    - https://www.geeksforgeeks.org/eof-and-feof-in-c/
 */
#include <stdio.h>
#include <stdlib.h>

#define ERR_ARGS "my-zip: file1 [file2 ...]"
#define ERR_FILE "Failed to open file."

/**
 * This function takes a file and iterates through each character.
 * A buffer is used to calculate how many same chars are in a row.
 * Once a differing char is found, the calculations are written 
 * into stdout. After that, the buffer is reset and calculations
 * based on the new char are made.
 *
 * Everything is stored in 5-byte entries, as required by the 
 * project assignment.
 */
void zipProcess(FILE* inputFile)
{
  // Fetching the first letter
  int current = fgetc(inputFile);
  int next;

  // Iterating through each character.
  while (current != EOF)
  {
    int numBuffer = 1;
    while ((next = fgetc(inputFile)) == current)
    {
      numBuffer++;
    }

    // Printing the results to stdout. The number is 4 bytes and the car is 1 byte.
    // This make the required 5-byte entry.
    fwrite(&numBuffer, 4, 1, stdout);
    fwrite(&current, sizeof(char), 1, stdout);
    current = next;
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
        zipProcess(fp);
        fclose(fp);
      }
      break;
  }
  return 0;
}
