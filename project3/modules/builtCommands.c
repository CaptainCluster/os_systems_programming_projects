/**
 * Built-in command for exiting the program
 */
void commandExit(char* const* arguments)
{
  if (arguments[1] == NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  exit(0);
}

void commandCd(char* const* arguments)
{
  // Exiting with error if this is not met: 0 < args < 2
  if (arguments[1] == NULL || arguments[2] != NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  if (chdir(arguments[1]) != 0)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
}
