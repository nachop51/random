#include "definitions.h"

/**
 * _strchr - Locates a character in a string
 * @s: String to be searched
 * @c: Character to be located
 * Return: Pointer to the first occurrence of the character
 * or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		++s;
	}
	return (NULL);
}

/**
 * _memset - Fills the first n bytes of the memory area pointed to by s
 * with the constant byte b
 * @s: Pointer to the memory area to be filled
 * @b: Constant byte to fill the memory area with
 * @n: Number of bytes to be filled
 * Return: Pointer to the filled memory area @s
 */
void *_memset(void *s, uint8_t b, uint32_t n)
{
	char *ptr = s;

	while (n--)
		*ptr++ = b;
	return (s);
}

/**
 * _strlen - Computes the length of a string
 * @s: String to be evaluated
 * Return: Length of the string
 */
uint32_t _strlen(char *s)
{
	uint32_t len = 0;

	while (*s++)
		++len;
	return (len);
}

/**
 * _strncmp - Compares two strings
 * @s1: First string to be compared
 * @s2: Second string to be compared
 * @n: Number of bytes to be compared
 *
 * Return: Difference between the first two different bytes
 */
uint8_t _strncmp(char *s1, char *s2, uint32_t n)
{
	while (*s1 && *s2 && n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		++s1, ++s2;
	}
	return (0);
}

/**
 * _strcpy - Copies the string pointed to by src, including the terminating
 * null byte, to the buffer pointed to by dest
 * @dest: Buffer to copy the string to
 * @src: String to be copied
 * Return: Pointer to the buffer
 */
char *_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
