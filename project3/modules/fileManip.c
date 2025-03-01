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

/**
 * Checking for EOF. Program ends if it is EOF.
 */ 
void checkEOF(FILE* inputFile)
{
  if (feof(inputFile))
  {
    exit(0);
  }
}

void openRedirect(char* (*arguments)[2048])
{
  FILE* fd;
  int j;
  for (j = 0 ; (*arguments)[j] != NULL ; j++)
  {
    if (!strstr((*arguments)[j], ">"))
    {
      printf("oo");
      continue;
    }
    if ((fd = fopen((*arguments)[j+1], "w")) == NULL)
    {
      exit(1);
    }
    dup2(fileno(fd), fileno(stdout));
    (*arguments)[j+1] = NULL;
    (*arguments)[j] = NULL;
    break;
  }
}
