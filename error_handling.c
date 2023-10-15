#include "header_shell_files.h"

/**
 * printErrorMessage_O - This function prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printErrorMessage_O(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		writeErrorChar(str[i]);
		i++;
	}
}

/**
 * writeErrorChar - This function writes the character c to standard error
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int writeErrorChar(char c)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == BUFFER_FLUSH || i >= BUFFER_SIZE_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * writeCharToFileDescriptor - This function writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToFileDescriptor(char c, int fd)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == BUFFER_FLUSH || i >= BUFFER_SIZE_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * writeStringToFileDescriptor - This function prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int writeStringToFileDescriptor(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += writeCharToFileDescriptor(*str++, fd);
	}
	return (i);
}
