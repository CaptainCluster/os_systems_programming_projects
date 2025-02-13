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
