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

/**
 * Allows content to be redirected into a file. 
 */
void openRedirect(char* (*arguments)[2048])
{
  FILE* fd;

  // Traversing until '>' is found. If it is not in the arguments array, no 
  // code in the loop executes.
  for (int j = 0 ; (*arguments)[j] != NULL ; j++)
  {
    // Moving to next argument if redirect symbol is not found
    if (!strstr((*arguments)[j], ">"))
    {
      continue;
    }

    // The redirect symbol has been found.
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
