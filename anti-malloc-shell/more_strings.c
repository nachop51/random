#include "shell.h"

/**
 * _strcat - Concatenates two strings
 * @dest: String to be appended to
 * @src: String to append
 * Return: Pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest + _strlen(dest);

	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}

/**
 * _strtok - Tokenizes a string
 * @str: String to be tokenized
 * @delim: Delimiter to tokenize the string with
 * Return: Pointer to the next token
 */
char *_strtok(char *str, char *delim)
{
	static char *ptr;
	char *tok = NULL;

	if (str)
		ptr = str;
	if (!ptr || !*ptr)
		return (NULL);
	while (*ptr && _strchr(delim, *ptr)) /* "  \t  \t ls\0" */
		ptr++;
	if (!*ptr)
	{
		ptr = NULL;
		return (NULL);
	}
	tok = ptr;
	while (*ptr && !_strchr(delim, *ptr))
		++ptr;
	if (*ptr)
		*ptr++ = '\0';
	else
		ptr = NULL;
	return (tok);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: Difference between the strings
 */
int32_t _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		++s1, ++s2;
	return (*s1 - *s2);
}
