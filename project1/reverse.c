#include <stdio.h>

int main(int argc, char** argv)
{

  /**
   * case 1 - No I/O files passed
   * case 2 - Input file passed
   * case 3 - I/O files passed 
   * Default - More than 2 arguments passed
   */ 
  switch(argc)
  {
    case 1:
      break;
    
    case 2:
      break;

    case 3:
      break;

    default:
      printf("You should only pass two args max: an input file and an output file.\n");
      break;
  }

  return 0;
}
