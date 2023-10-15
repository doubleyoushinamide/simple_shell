#include "header_shell_files.h"

/**
 * clearInfo - This function initializes arg_u struct
 * @info: This is the struct address
 */
void clearInfo(arg_u *info)
{
	info->arg_str = NULL;
	info->arg_array = NULL;
	info->cmd_path = NULL;
	info->arg_count = 0;
}

/**
 * setInfo - initializes arg_u struct
 * @info: struct address
 * @argv: argument vector
 */
void setInfo(arg_u *info, char **argv)
{
	int index = 0;

	info->filename = argv[0];
	if (info->arg_str)
	{
		info->arg_array = tokenizeString(info->arg_str, " \t");
		if (!info->arg_array)
		{
			info->arg_array = malloc(sizeof(char *) * 2);
			if (info->arg_array)
			{
				info->arg_array[0] = stringDuplicate(info->arg_str);
				info->arg_array[1] = NULL;
			}
		}
		for (index = 0; info->arg_array && info->arg_array[index]; index++)
			;

		info->arg_count = index;

		replaceAlias(info);
		replaceVars(info);
	}
}

/**
 * freeInfo - This function frees arg_u struct fields
 * @info: This is the struct address
 * @all: True for freeing all the fields
 */
void freeInfo(arg_u *info, int all)
{
	freeMemory(info->arg_array);
	info->arg_array = NULL;
	info->cmd_path = NULL;

	if (all)
	{
		if (!info->cmd_buffer)
			free(info->arg_str);
		if (info->env_list)
			freeList(&(info->env_list));
		if (info->history_list)
			freeList(&(info->history_list));
		if (info->alias_list)
			freeList(&(info->alias_list));
		freeMemory(info->environ);
			info->environ = NULL;
		freeBlock((void **)info->cmd_buffer);
		if (info->read_fd > 2)
			close(info->read_fd);
		printCharacter(BUFFER_FLUSH);
	}
}
