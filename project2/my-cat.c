#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int i;

  // Exiting if no files are provided
  if (argc == 1 )
  {
    exit(0);
  }

  for (i = 1 ; i < argc ; i++)
  {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
      printf("Cannot open file.\n");
      exit(1);
    }
  }

  printf("Hello, World!\n");
  return 0;
}
