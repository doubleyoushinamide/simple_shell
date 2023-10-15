#include "header_shell_files.h"

/**
 * getEnvironmentVariables - This function returns
 * the string array copy of our environ
 * @info: This is the argument struct
 * Return:	Returns an array of strings
 *		containing environment variables
 */
char **getEnvironmentVariables(arg_u *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listToStrings(info->env_list);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetEnvironmentVariable - This function
 * removes an environment variable
 * @info: This is the argument struct
 * @var: This is the string environment variable property
 * Return: 1 on delete, 0 otherwise
 */
int unsetEnvironmentVariable(arg_u *info, char *var)
{
	list_s *node = info->env_list;
	size_t index = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->string, var);
		if (p && *p == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env_list), index);
			index = 0;
			node = info->env_list;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * setEnvironmentVariable - This function initialize a new
 * environment variable, or modify an existing one
 * @info: This is the argument struct
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int setEnvironmentVariable(arg_u *info, char *var, char *value)
{
	char *buffer = NULL;
	list_s *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(stringLength(var) + stringLength(value) + 2);
	if (!buffer)
		return (1);
	stringCopy_O(buffer, var);
	stringConcatenate_O(buffer, "=");
	stringConcatenate_O(buffer, value);
	node = info->env_list;
	while (node)
	{
		p = startsWith(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env_list), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
