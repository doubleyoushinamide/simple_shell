#include "header_shell_files.h"

/**
 * cusInputBuf - This function buffers chained commands
 * @info: This is the argument struct
 * @buffer: This is the address of the buffer
 * @length: The address of the length variable
 *
 * Return: This returns the bytes read
 */
ssize_t cusInputBuf(arg_u *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t leng = 0;

	if (!*length)
	{
		/*freeBlock((void **)info->cmd_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if SYSTEM_USE_GETLINE
		bytes_read = getline(buffer, &leng, stdin);
#else
		bytes_read = customGetLine(info, buffer, &leng);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->count_flag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->history_count++);
			/* if (stringSearch(*buffer, ';')) is this a command chain? */
			{
				*length = bytes_read;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * getInput - This function gets a line minus the newline
 * @info: This is the argument struct
 *
 * Return: Returns bytes read
 */
ssize_t getInput(arg_u *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t index, pos, len;
	ssize_t bytes_read = 0;
	char **bufferP = &(info->arg_str), *p;

	printCharacter(BUFFER_FLUSH);
	bytes_read = cusInputBuf(info, &buffer, &len);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (len)
	{
		pos = index;
		p = buffer + index;

		checkChain(info, buffer, &pos, index, len);
		while (pos < len)
		{
			if (isChain(info, buffer, &pos))
				break;
			pos++;
		}

		index = pos + 1;
		if (index >= len)
		{
			index = len = 0;
			info->cmd_buffer_type = NORMAL;
		}

		*bufferP = p;
		return (stringLength(p));
	}

	*bufferP = buffer;
	return (bytes_read);
}

/**
 * readBuffer - This function reads a buffer
 * @info: This is the argument struct
 * @buffer: This is a buffer
 * @s: size
 *
 * Return: Returns bytes read
 */
ssize_t readBuffer(arg_u *info, char *buffer, size_t *s)
{
	ssize_t bytes_read = 0;

	if (*s)
		return (0);
	bytes_read = read(info->read_fd, buffer, BUFFER_SIZE_READ);
	if (bytes_read >= 0)
		*s = bytes_read;
	return (bytes_read);
}

/**
 * customGetLine - This function gets the next line of input from STDIN
 * @info: This is the argument struct
 * @point: This is the address of pointer to the buffer
 * @length: This is the size of the preallocated pointer buffer if not NULL
 *
 * Return: Number of characters of the line read (chars_read)
 */
int customGetLine(arg_u *info, char **point, size_t *length)
{
	static char buffer[BUFFER_SIZE_READ];
	static size_t index, leng;
	size_t k;
	ssize_t bytes_read = 0, chars_read = 0;
	char *p = NULL, *newP = NULL, *c;

	p = *point;
	if (p && length)
		chars_read = *length;
	if (index == leng)
		index = leng = 0;

	bytes_read = readBuffer(info, buffer, &leng);
	if (bytes_read == -1 || (bytes_read == 0 && leng == 0))
		return (-1);

	c = stringSearch(buffer + index, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : leng;
	newP = customRealloc(p, chars_read, chars_read ? chars_read + k : k + 1);
	if (!newP)
		return (p ? (free(p), -1) : -1);

	if (chars_read)
		stringConcatenate(newP, buffer + index, k - index);
	else
		stringCopy(newP, buffer + index, k - index + 1);

	chars_read += k - index;
	index = k;
	p = newP;

	if (length)
		*length = chars_read;
	*point = p;
	return (chars_read);
}

/**
 * sigintHandler - This function blocks the ctrl-C command
 * @sigNum: This is the signal number
 *
 * Return: Returns nothing
 */
void sigintHandler(__attribute__((unused))int sigNum)
{
	printString("\n");
	printString("$ ");
	printCharacter(BUFFER_FLUSH);
}
