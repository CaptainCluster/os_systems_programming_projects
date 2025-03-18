#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE    1024

/**
 * Reading the content of the file by putting it in a buffer. 
 * Then the content of the buffer is compared to the grep 
 * search term. If there is a match, the buffer is printed.
 */
void readContent(FILE* fp, char* grepTerm)
{
  char buffer[BUFFER_SIZE];
  
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    if (strstr(buffer, grepTerm) != NULL)
    {
      printf("%s", buffer);
    }
  }
}

int main(int argc, char** argv)
{
  int i;

  /**
   * A switch-case that handles things based on how many args 
   * have been given
   *
   * Scenarios
   * =========
   * No arguments - The prorgram prints a line, explaining how
   * things should be handled and then exits.
   *
   * 1 argument - Search term is received and lines received 
   * from standard input are being compared to.
   *
   * Default (2<= number of argument) - Search term is received
   * and all other arguments are assumed to be file names. The 
   * program attempts to open the files. If it fails, the program
   * exits.
   */
  switch(argc)
  {
    case 1:
      printf("my-grep: searchterm [file ...]\n");
      exit(1);
    case 2:
      readContent(stdin, argv[1]);
    default:
      for (i = 2 ; i < argc ; i++)
      {
        FILE *fp = fopen(argv[i], "r");

        // Should opening the file fail, it will be closed
        if (fp == NULL)
        {
          printf("my-grep: cannot open file.\n");
          exit(1);
        }
        // Reading content, then closing the file
        readContent(fp, argv[1]);
        fclose(fp);
      }
  }
  return 0;
}

