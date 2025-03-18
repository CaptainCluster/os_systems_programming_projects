/**
 * This file contains a bunch of constant variables
 */

char error_message[30] = "An error has occurred\n";

#define BUFFER_SIZE    2048

#define ERR_INPUTFILE  "Error when attempting to open the input file!\n"
#define ERR_MALLOC     "Failed to allocate memory!\n"
#define ERR_NO_PATH    "No valid path found! Wrong path? Do you have the command?\n"
#define ERR_PROCESS    "Encountered a process-related error!\n"
#define ERR_FILEOPEN   "Failed to open file!\n"
#define ERR_EXITARGS   "The exit command should not be given any args!\n"
#define ERR_CDARGNUM   "The cd command was provided an inadequate amount of args!\n"
#define ERR_CDFAIL     "Failed to change directory!\n"

#define ARGS_DELIM     " "
#define CMD_DELIM      "&"
