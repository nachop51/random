#include "shell.h"
#include <stdarg.h>

/**
 * _putc - Prints a character to a file descriptor
 * @fd: File descriptor to print to
 * @c: Character to be printed
 */
static void _putc(uint8_t fd, char c)
{
	write(fd, &c, 1);
}

/**
 * p_int_recursion - Prints an integer recursively
 * @fd: File descriptor to print to
 * @n: Number to be printed
 */
static void p_int_recursion(uint8_t fd, uint32_t n)
{
	if (n > 10)
	{
		p_int_recursion(fd, n / 10);
		_putc(fd, n % 10 + '0');
		return;
	}
	_putc(fd, (n % 10) + '0');
}

/**
 * p_int - Prints an integer
 * @fd: File descriptor to print to
 * @args: List of arguments
 */
static void p_int(uint8_t fd, va_list args)
{
	int32_t n = va_arg(args, int32_t);

	if (n < 0)
		_putc(fd, '-'), n = -n;
	p_int_recursion(fd, n);
}

/**
 * p_str - Prints a string
 * @fd: File descriptor to print to
 * @args: List of arguments
 */
static void p_str(uint8_t fd, va_list args)
{
	char *str = va_arg(args, char *);

	if (!str)
		str = "(null)";
	write(fd, str, strlen(str));
}

/**
 * _dprintf - Prints a string to a file descriptor
 * @fd: File descriptor to print to
 * @format: Format of the string to be printed
 * @...: Arguments to be passed to the format string
 */

void _dprintf(uint8_t fd, const char *format, ...)
{
	va_list args;
	uint8_t i = 255;

	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			switch (format[++i])
			{
			case 'd':
				p_int(fd, args);
				break;
			case 's':
				p_str(fd, args);
				break;
			default:
				return;
			}
		}
		else
			_putc(fd, format[i]);
	}
	va_end(args);
}
