#include "shell.h"
#include <stdlib.h>

/**
 * _getenv - Gets the value of an environment variable
 * @var: Name of the environment variable
 * @buffer: Buffer to store the value of the environment variable
 * Return: Pointer to the buffer
 */
static char *_getenv(char *var, char *buffer)
{
	char *tok = NULL;
	uint16_t i = 0;

	while (environ[i])
	{
		if (_strncmp(environ[i], var, _strlen(var)) == 0)
		{
			if (environ[i][_strlen(var)] != '=')
				continue;
			tok = _strchr(environ[i], '=');
			_strcpy(buffer, tok + 1);
			return (buffer);
		}
		++i;
	}
	return (NULL);
}

/**
 * solve_path - Solves the path of a command
 * @buff: Buffer to store the path
 * @cmd: Command to be solved
 * Return: 1 if the command was found, 0 otherwise
 */
static int8_t solve_path(char *buff, char *cmd)
{
	char *tok = NULL, path[1024] = {0};

	_getenv("PATH", path);
	if (path[0] == '\0')
		return (0);
	tok = _strtok(path, ":");
	while (tok)
	{
		_strcpy(buff, tok), _strcat(buff, "/"), _strcat(buff, cmd);
		if (access(buff, F_OK) == 0)
			return (1);
		tok = _strtok(NULL, ":");
	}
	return (0);
}

/**
 * built_in - Checks if the command is a built-in
 * @args: Arguments to be passed to the command
 * @error: Error code of the last command executed
 *
 * Return: 1 if the command is a built-in, -1 otherwise
 */
static int8_t built_in(char **args, uint8_t *error)
{
	if (strcmp(args[0], "env") == 0)
	{
		uint16_t i = 0;

		while (environ[i])
			write(1, environ[i], strlen(environ[i])), i += write(1, "\n", 1);
		return (1);
	}
	else if (strcmp(args[0], "exit") == 0)
		exit(*error);
	return (-1);
}

/**
 * tokenize_line - Tokenizes the input string
 * @line: Struct to store the input string, command and arguments
 * Return: 1 if there is something to tokenize, 0 otherwise
 */
static int8_t tokenize_line(struct cmd_t *line)
{
	char *tok = _strtok(line->string, "\n");
	int8_t i = -1;

	if (!tok)
		return (0);
	tok = _strtok(line->string, " \t\n");
	while (tok != NULL)
		line->args[++i] = tok, tok = _strtok(NULL, " \t\n");
	line->args[++i] = NULL;

	if (line->args[0] == NULL)
		return (0);
	return (1);
}

/**
 * evaluate_input - Evaluates the input and returns the command and arguments
 * @line: Struct to store the input string, command and arguments
 * @error: Error code of the last command executed
 *
 * Return: 0 if the command was found, 1 otherwise
 */
int8_t evaluate_input(struct cmd_t *line, uint8_t *error)
{
	if (!tokenize_line(line))
		return (0);

	if (line->args[0][0] != '/' && solve_path(line->cmd, line->args[0]))
		line->args[0] = line->cmd;

	if (access(line->args[0], F_OK) == -1) /* Command not found */
	{
		if (built_in(line->args, error) != -1)
			return (1);
		_dprintf(2, "%s: %d: %s: not found\n", line->pname,
				 line->number, line->args[0]);
		*error = 127;
		return (0);
	}

	return (1);
}
