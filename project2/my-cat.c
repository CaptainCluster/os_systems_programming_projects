#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE    1024

/**
 * Reading the contents of the file. Has a buffer ready to read content
 * until EOF is met. The content in the buffer is written in a loop.
 */ 
void readContent(FILE* fp)
{
  char buffer[BUFFER_SIZE];
  
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    printf("%s", buffer);
  }
}

int main(int argc, char** argv)
{
  int i;

  // Exiting if no files are provided
  if (argc == 1 )
  {
    exit(0);
  }

  // Iterating through each provided file.
  for (i = 1 ; i < argc ; i++)
  {
    FILE *fp = fopen(argv[i], "r");
    
    // Should opening the file fail, it will be closed
    if (fp == NULL)
    {
      printf("Cannot open file.\n");
      exit(1);
    }

    // Reading content, then closing the file
    readContent(fp);
    fclose(fp);
  }
  return 0;
}
