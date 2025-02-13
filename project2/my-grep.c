#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE    1024

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
          printf("Cannot open file.\n");
          exit(1);
        }
        // Reading content, then closing the file
        readContent(fp, argv[1]);
        fclose(fp);
      }
  }
  return 0;
}

