#include "header_shell_files.h"

/**
 * getHistoryFile - This function gets the history of the file
 * @info: The argument struct
 *
 * Return: The allocated string containing history file
 */
char *getHistoryFile(arg_u *info)
{
	char *buffer, *dir;

	dir = getEnvironmentVariable(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (stringLength(dir)
				+ stringLength(HISTORY_FILE_NAME) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	stringCopy_O(buffer, dir);
	stringConcatenate_O(buffer, "/");
	stringConcatenate_O(buffer, HISTORY_FILE_NAME);
	return (buffer);
}

/**
 * writeHistory - This function creates a new file
 * or appends to an existing file
 * @info: This is the argument struct
 *
 * Return: 1 on success, else -1
 */
int writeHistory(arg_u *info)
{
	ssize_t fd;
	char *fname = getHistoryFile(info);
	list_s *nodes = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (nodes = info->history_list; nodes; nodes = nodes->next)
	{
		writeStringToFileDescriptor(nodes->string, fd);
		writeCharToFileDescriptor('\n', fd);
	}
	writeCharToFileDescriptor(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistory - This function reads the history from the file
 * @info: This is the argument struct
 *
 * Return: On success, return history count, otherwise return 0
 */
int readHistory(arg_u *info)
{
	int index, end = 0, lineCount = 0;
	ssize_t fd, rdleng, fsize = 0;
	struct stat st;
	char *buffer = NULL, *fname = getHistoryFile(info);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdleng = read(fd, buffer, fsize);
	buffer[fsize] = '\0';
	if (rdleng <= 0)
		return (free(buffer), 0);
	close(fd);
	for (index = 0; index < fsize; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = '\0';
			buildHistoryList(info, buffer + end, lineCount++);
			end = index + 1;
		}
	if (end != index)
		buildHistoryList(info, buffer + end, lineCount++);
	free(buffer);
	info->history_count = lineCount;
	while (info->history_count-- >= HISTORY_MAX_ENTRIES)
		deleteNodeAtIndex(&(info->history_list), 0);
	renumberHistory(info);
	return (info->history_count);
}

/**
 * buildHistoryList - This function adds entry to a history linked list
 * @info: This is the argument struct
 * @buffer: This is a buffer
 * @lineCount: This is the history of the linecount
 *
 * Return: Always 0
 */
int buildHistoryList(arg_u *info, char *buffer, int lineCount)
{
	list_s *nodes = NULL;

	if (info->history_list)
		nodes = info->history_list;
	addNodeEnd(&nodes, buffer, lineCount);

	if (!info->history_list)
		info->history_list = nodes;
	return (0);
}

/**
 * renumberHistory - This function renumbers the
 * history linked list after changes
 * @info: This is the argument struct
 *
 * Return: The new history count is returned
 */
int renumberHistory(arg_u *info)
{
	list_s *nodes = info->history_list;
	int index = 0;

	while (nodes)
	{
		nodes->number = index++;
		nodes = nodes->next;
	}
	return (info->history_count = index);
}
