#include "header_shell_files.h"

/**
 * convertToIntWithErrorCheck - This function converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int convertToIntWithErrorCheck(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * printError - This function prints an error message
 * @info: the parameter & return struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printError(arg_u *info, char *str)
{
	printErrorMessage_O(info->filename);
	printErrorMessage_O(": ");
	printDigit(info->error_count, STDERR_FILENO);
	printErrorMessage_O(": ");
	printErrorMessage_O(info->arg_array[0]);
	printErrorMessage_O(": ");
	printErrorMessage_O(str);
}

/**
 * printDigit - This function prints a decimal number
 * @insert: input strings
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printDigit(int insert, int fd)
{
	int (*__putchar)(char) = printCharacter;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = writeErrorChar;
	if (insert < 0)
	{
		_abs_ = -insert;
		__putchar('-');
		count++;
	}
	else
		_abs_ = insert;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertNumber - This function converts a function.
 * @number: number
 * @base: base
 * @flag: argument flags
 *
 * Return: string
 */
char *convertNumber(long int number, int base, int flag)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flag & NUMBER_CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = (flag & NUMBER_CONVERT_LOWERCASE)
			? "0123456789abcdef"[n % base] :
			"0123456789ABCDEF"[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * removeComments - This function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: void
 */
void removeComments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (i == 0 || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}
