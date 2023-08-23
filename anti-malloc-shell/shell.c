#include "shell.h"

/**
 * _getline - Anti-malloc implementation of getline
 * @lineptr: Pointer to the input string
 * @n: Size of the input string
 * Return: Number of characters read
 */
static int8_t _getline(char *lineptr, uint16_t n)
{
	char c = 0;
	uint16_t i = 0;

	while (c != '\n' && i < n)
	{
		if (read(0, &c, 1) == 0)
			return (EOF);
		lineptr[i++] = c;
		if (c == '\n')
			break;
	}
	lineptr[i] = '\0';
	return (i);
}

/**
 * execute_input - Executes a command
 * @args: Arguments to be passed to the command
 * @error: Error code of the last command executed
 * Return: 1 if the command was executed successfully, 0 otherwise
 */
static uint8_t execute_input(char **args, uint8_t *error)
{
	int32_t status;

	if (args[0] == NULL)
		return (1);
	switch (fork())
	{
	case -1:
		_dprintf(2, "%s: Fork failed\n", args[0]);
		return (0);
	case 0:
		if (execve(args[0], args, environ) == -1)
		{
			_dprintf(2, "%s: Something went wrong\n", args[0]);
			return (0);
		}
		break;
	default:
		wait(&status);
		*error = WIFEXITED(status) ? WEXITSTATUS(status) : 0;
		break;
	}
	return (1);
}

/**
 * reset_line - Resets the line struct and calls getline
 * @line: Struct to store the input string, command and arguments
 * Return: 1 if the line was reset, 0 otherwise
 */
static uint8_t reset_line(struct cmd_t *line)
{
	_memset(line->args, 0, 128);
	_memset(line->cmd, 0, 256);
	line->number++;
	if (isatty(STDIN_FILENO))
		_dprintf(1, "$ ");
	if (_getline(line->string, 1024) == EOF)
		return (0);
	return (1);
}

/**
 * main - Shell entry point
 * @ac: Number of arguments passed to the shell
 * @av: Arguments passed to the shell
 *
 * Return: Error code of the last command executed or 0 if no error
 */
int32_t main(__attribute__((unused)) int32_t ac, char **av)
{
	struct cmd_t line = {{0}, {0}, {0}, 0, 0};
	uint8_t error = 0, ret = 0;

	line.pname = av[0];
	while (reset_line(&line))
	{
		ret = evaluate_input(&line, &error);

		if (ret == NOTHING || ret == BUILT_IN)
			continue;
		if (ret == EXIT_BUILTIN || !execute_input(line.args, &error))
			break;
	}
	return (error);
}
