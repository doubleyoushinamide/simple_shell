#include "header_shell_files.h"

/**
 * executeEnvCommand - prints the current environment
 * @info: Structure containing potential argument
 * Return: Always 0
 */

int executeEnvCommand(arg_u *info)
{
	printListString(info->env_list);
	return (0);
}

/**
 * getEnvironmentVariable - This function gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: env variable name
 *
 * Return: the value of the env variable
 */

char *getEnvironmentVariable(arg_u *info, const char *name)
{
	list_s *node = info->env_list;
	char *p;

	while (node)
	{
		p = startsWith(node->string, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * executeSetenvCommand - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int executeSetenvCommand(arg_u *info)
{
	if (info->arg_count != 3)
	{
		printErrorMessage_O("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnvironmentVariable(info, info->arg_array[1], info->arg_array[2]))
		return (0);
	return (1);
}

/**
 * executeUnsetenvCommand - Remove an environment variable
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int executeUnsetenvCommand(arg_u *info)
{
	int i;

	if (info->arg_count == 1)
	{
		printErrorMessage_O("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i < info->arg_count; i++)
		unsetEnvironmentVariable(info, info->arg_array[i]);

	return (0);
}

/**
 * populateEnvironmentList - populates env linked list
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int populateEnvironmentList(arg_u *info)
{
	list_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	info->env_list = node;
	return (0);
}
