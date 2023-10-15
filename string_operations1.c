#include "header_shell_files.h"

/**
 * stringCopy_O - This is a function that copies a string
 * @dest: This is the destination copied to
 * @src: This is the source from which it was copied
 *
 * Return: Returns the pointer to destination
 */
char *stringCopy_O(char *dest, char *src)
{
	int strIndex = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[strIndex])
	{
		dest[strIndex] = src[strIndex];
		strIndex++;
	}
	dest[strIndex] = '\0';
	return (dest);
}

/**
 * stringDuplicate - This is a function that duplicates a string
 * @str: This is the string to be duplicated
 *
 * Return: Returns the pointer to the duplicated string
 */
char *stringDuplicate(const char *str)
{
	int length = 0;
	char *ret;
	int i;

	if (str == NULL)
		return (NULL);

	while (str[length])
		length++;

	ret = malloc((length + 1) * sizeof(char));
	if (!ret)
		return (NULL);

	for (i = 0; i < length; i++)
		ret[i] = str[i];

	return (ret);
}

/**
 * printString - This is a function that prints an input string
 * @str: This is the string to be printed
 *
 * Return: Nothing to return
 */
void printString(char *str)
{
	int strIndex = 0;

	if (!str)
		return;

	while (str[strIndex] != '\0')
	{
		printCharacter(str[strIndex]);
		strIndex++;
	}
}

/**
 * printCharacter - This function writes the character c to stdout
 * @c: This is the character to print
 *
 * Return: On success, returns 1.
 *         On error, returns -1.
 */
int printCharacter(char c)
{
	static int strIndex;
	static char buffer[BUFFER_SIZE_WRITE];

	if (c == BUFFER_FLUSH || strIndex >= BUFFER_SIZE_WRITE)
	{
		write(1, buffer, strIndex);
		strIndex = 0;
	}

	if (c != BUFFER_FLUSH)
		buffer[strIndex++] = c;

	return (1);
}
