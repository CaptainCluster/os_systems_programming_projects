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
