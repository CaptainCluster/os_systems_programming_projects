/**
 * Prints the prompt, aka wish> (Wisconsin shell). The prompt will 
 * be printed only if the commands are received from standard input.
 */
void printPrompt(int argc)
{
  if (argc == 1)
  {
    printf("wish> ");
  }
}

/**
 * Removes a new line from a string
 */
void removeNewLine(char** string)
{
  if ((*string)[strlen(*string)-1] == '\n')
  {
    (*string)[strlen(*string)-1] = 0; 
  }
}
