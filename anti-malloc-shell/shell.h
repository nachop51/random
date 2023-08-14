#ifndef SHELL_H
#define SHELL_H

#include "definitions.h"
#include "shell_string.h"

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * struct cmd_t - Struct to store the input string, command and arguments
 * @string: Input string
 * @cmd: Command
 * @args: Arguments
 * @pname: Program name
 * @number: Number of the command
 */
struct cmd_t
{
	char string[1024], cmd[256], *args[32], *pname;
	__uint16_t number;
};

__int8_t evaluate_input(struct cmd_t *line, __uint8_t *error);
void _dprintf(__uint8_t fd, const char *format, ...);

#endif /* SHELL_H */
