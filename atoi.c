#include "header_shell_files.h"

/**
 * interactive - returns true (1) if shell is interactive
 * @info: This is the structure address
 *
 * Return: (1) if interactive mode, 0 otherwise
 */
int interactive(arg_u *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * isDelimiter - This function verifies if the
 * character from input is a delimeter
 * @c: the char to check
 * @delimiters: the delimeter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char c, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == c)
			return (1);
	return (0);
}

/**
 * isAlphabetic - this function checks for alphabetic characters
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertToInt - this function converts a input str to int
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int convertToInt(char *s)
{
	int i, sng = 1, flg = 0, out;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flg != 2; i++)
	{
		if (s[i] == '-')
			sng *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flg = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sng == -1)
		out = -result;
	else
		out = result;

	return (out);
}
