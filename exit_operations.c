#include "header_shell_files.h"

/**
 **stringCopy - This function copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *stringCopy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
		dest[i] = src[i];

	if (i < n)
	{
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}

	return (dest);
}

/**
 **stringConcatenate - This function concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *stringConcatenate(char *dest, char *src, int n)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
		dest[i] = '\0';

	return (dest);
}

/**
 **stringSearch - This function locates a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *stringSearch(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}

	return (NULL);
}
