#include "shell.h"
#include <stdio.h>

/**
 * _getenv - Gets the value of an environment variable
 * @var: Name of the environment variable
 * @buffer: Buffer to store the value of the environment variable
 * Return: Pointer to the buffer
 */
char *_getenv(char *var, char *buffer)
{
	char *tok = NULL;
	__uint16_t i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], var, strlen(var)) == 0)
		{
			tok = strchr(environ[i], '=');
			strcpy(buffer, tok + 1);
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
__int8_t solve_path(char *buff, char *cmd)
{
	char *tok = NULL, path[1024] = {0};

	_getenv("PATH", path);
	if (path[0] == '\0')
		return (0);
	tok = strtok(path, ":");
	while (tok)
	{
		strcpy(buff, tok), strcat(buff, "/"), strcat(buff, cmd);
		if (access(buff, F_OK) == 0)
			return (1);
		tok = strtok(NULL, ":");
	}
	return (0);
}

/**
 * _getline - Anti-malloc implementation of getline
 * @lineptr: Pointer to the input string
 * @n: Size of the input string
 * Return: Number of characters read
 */
__int8_t _getline(char *lineptr, __uint64_t n)
{
	char c = 0;
	__uint64_t i = 0;

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
