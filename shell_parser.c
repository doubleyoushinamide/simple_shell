#include "header_shell_files.h"

/**
 * isCmd - This function determines if a file
 * is an executable command
 * @info: This is the argument structure
 * @path: This specifies the path to the file
 * in the current working directory
 *
 * Return: 1 if true, 0 otherwise
 */
int isCmd(arg_u *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupChars - This function is to duplicate characters
 * @str: This is the string passed to duplicate characters
 * @start: This is where the index starts
 * @end: This is the end index
 *
 * Return: Returns the pointer to the new buffer
 */
char *dupChars(char *str, int start, int end)
{
	static char buffer[1024];
	int index = 0, k = 0;

	for (k = 0, index = start; index < end; index++)
	{
		if (str[index] != ':')
			buffer[k++] = str[index];
	}
	buffer[k] = '\0';
	return (buffer);
}

/**
 * findPath - This function finds the command in the PATH string
 * @info: This is the argument structure
 * @pathString: This is the PATH string
 * @cmd: This is the command to find
 *
 * Return:	Returns the full path of the command if found
 *		NULL if not found
 */
char *findPath(arg_u *info, char *pathString, char *cmd)
{
	int index = 0, currPos = 0;
	char *path;

	if (!pathString)
		return (NULL);
	if ((stringLength(cmd) > 2) && startsWith(cmd, "./"))
	{
		if (isCmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathString[index] || pathString[index] == ':')
		{
			path = dupChars(pathString, currPos, index);
			if (!path || stringLength(path) == 0)
				stringConcatenate_O(path, cmd);
			else
			{
				stringConcatenate_O(path, "/");
				stringConcatenate_O(path, cmd);
			}
			if (isCmd(info, path))
				return (path);
			if (!pathString[index])
				break;
			currPos = index;
		}
		index++;
	}
	return (NULL);
}
