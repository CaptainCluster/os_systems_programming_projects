#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE    1024

int main() 
{
  char error_message[30] = "An error has occurred\n";
  char* buffer;
  size_t bufferSize = BUFFER_SIZE;
	
  while (1) 
	{
    printf("wish> ");

    if ((buffer = (char*) malloc(BUFFER_SIZE * sizeof(char))) == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1); 
    }
    getline(&buffer, &bufferSize, stdin);

    if (strstr(buffer, "exit"))
    {
      printf("bye");
      exit(0);
    }
    else if (strstr(buffer, "cd"))
    {
      printf("yo");
    }
    else if (strstr(buffer, "path"))
    {
      printf("hey");
    }
    else
    {
      printf("invalid input");
    }
	}
}

