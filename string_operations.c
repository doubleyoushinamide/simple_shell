#include "header_shell_files.h"

/**
 * stringLength - This function gives the length of a string
 * @str: This is the string whose length is checked
 *
 * Return: length of string (int)
 */
int stringLength(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;

	return (length);
}

/**
 * stringCompare - This function compares two strings lexically
 * @str1: This is the first string
 * @str2: This is the second string
 *
 * Return:	zero if str1 == str2
 *		positive if s1 > s2
 *		negative if s1 < s2
 */
int stringCompare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * startsWith - This function is to check if a string
 * starts with a given prefix
 * @str: This is the string to check
 * @prefix: This is the prefix to find
 *
 * Return: Returns the pointer to the next character of str
 * if prefix is found, otherwise NULL
 */
char *startsWith(const char *str, const char *prefix)
{
	if (str == NULL || prefix == NULL)
		return (NULL);

	while (*prefix)
	{
		if (*prefix++ != *str++)
			return (NULL);
	}

	return ((char *)str);
}

/**
 * stringConcatenate_O - This function concatenates two strings
 * @dest: This is the destination buffer
 * @src: This is the source buffer
 *
 * Return: Returns the pointer to the destination buffer
 */
char *stringConcatenate_O(char *dest, char *src)
{
	char *ptr = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;

	return (ptr);
}
