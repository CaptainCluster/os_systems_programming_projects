void processExit(char* const* arguments)
{
  printf("wee\n");
  if (arguments[1] != NULL)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }
  exit(0);
}
