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
