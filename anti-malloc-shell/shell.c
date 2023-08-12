#include "shell.h"

#include <stdio.h>

/**
 * built_in - Checks if the command is a built-in
 * @args: Arguments to be passed to the command
 * Return: 1 if the command is a built-in, -1 otherwise
 */
__int8_t built_in(char **args)
{
	if (strcmp(args[0], "env") == 0)
	{
		__uint16_t i = 0;

		while (environ[i])
			write(1, environ[i], strlen(environ[i])), ++i;
		return (1);
	}
	else if (strcmp(args[0], "exit") == 0)
		exit(0);
	return (-1);
}

/**
 * evaluate_input - Evaluates the input and returns the command and arguments
 * @lineptr: Pointer to the input string
 * @cmd: Pointer to the command string
 * @args: Pointer to the arguments array
 *
 * Return: 0 if the command was found, 1 otherwise
 */
__int8_t evaluate_input(char *lineptr, char *cmd, char **args)
{
	char *tok = strtok(lineptr, "\n");
	__int8_t i = -1;

	if (!tok)
		return (0);
	tok = strtok(lineptr, " \t\n");
	while (tok != NULL)
		args[++i] = tok, tok = strtok(NULL, " \t\n");
	args[++i] = NULL;

	if (args[0] == NULL)
		return (1);

	if (args[0][0] != '/')
		if (solve_path(cmd, args[0]))
			args[0] = cmd;

	if (access(args[0], F_OK) == -1) /* Command not found */
	{
		if (built_in(args) != -1)
			return (1);
		write(2, args[0], strlen(args[0]));
		write(2, ": Command not found. :(\n", 25);
		return (1);
	}
	return (0);
}

/**
 * execute_input - Executes a command
 * @args: Arguments to be passed to the command
 * @error: Error code of the last command executed
 * Return: 1 if the command was executed successfully, 0 otherwise
 */
__uint8_t execute_input(char **args, char *error)
{
	__int32_t pid = -1, status;

	if (args[0] == NULL)
		return (1);
	pid = fork();
	if (pid == -1)
		write(2, "Fork failed", 12), exit(1);
	if (pid == 0)
		if (execve(args[0], args, environ) == -1)
		{
			write(2, args[0], strlen(args[0])), write(2, ": Nope. :(\n", 12);
			return (0);
		}
	wait(&status), WIFEXITED(status) ? *error = WEXITSTATUS(status) : 0;
	return (1);
}

/**
 * main - Shell entry point
 *
 * Return: Error code of the last command executed or 0 if no error
 */
__int32_t main(void)
{
	char lineptr[1024] = {0}, *args[32], error = 0, cmd[256];

	while (memset(args, 0, 128) && memset(cmd, 0, 256))
	{
		isatty(STDIN_FILENO) ? write(1, "$ ", 2) : 0;
		if (_getline(lineptr, 1024) == EOF)
			break;
		if (evaluate_input(lineptr, cmd, args) == 1)
			continue;
		if (!execute_input(args, &error))
			break;
	}
	return (error);
}
