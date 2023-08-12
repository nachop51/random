#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

__int8_t _getline(char *lineptr, __uint64_t n);
__int8_t solve_path(char *buff, char *cmd);

extern char **environ;

#endif /* SHELL_H */
