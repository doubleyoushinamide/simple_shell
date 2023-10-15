#include "header_shell_files.h"

/**
 * isChain - This tests if the current character in the buffer
 * is a chain delimiter
 * @info: This is the argument struct
 * @buffer: This is the character buffer
 * @position: This is the address of the current position in buffer
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int isChain(arg_u *info, char *buffer, size_t *position)
{
	size_t k = *position;

	if (buffer[k] == '|' && buffer[k + 1] == '|')
	{
		buffer[k] = 0;
		k++;
		info->cmd_buffer_type = OR_CONDITION;
	}
	else if (buffer[k] == '&' && buffer[k + 1] == '&')
	{
		buffer[k] = 0;
		k++;
		info->cmd_buffer_type = AND_CONDITION;
	}
	else if (buffer[k] == ';')
	{
		buffer[k] = 0;
		info->cmd_buffer_type = COMMAND_CHAIN;
	}
	else
		return (0);

	*position = k;
	return (1);
}

/**
 * checkChain - This checks if we should continue chaining
 * based on the last status
 * @info: This is the argument struct
 * @buffer: This is the character buffer
 * @position: This is the address of the current position in buffer
 * @start: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void checkChain(arg_u *info, char *buffer, size_t *position, size_t start,
		size_t length)
{
	size_t k = *position;

	if (info->cmd_buffer_type == AND_CONDITION)
	{
		if (info->last_status)
		{
			buffer[start] = 0;
			k = length;
		}
	}
	if (info->cmd_buffer_type == OR_CONDITION)
	{
		if (!info->last_status)
		{
			buffer[start] = 0;
			k = length;
		}
	}

	*position = k;
}

/**
 * replaceAlias - This replaces aliases in the tokenized string
 * @info: This is the argument struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(arg_u *info)
{
	int index;
	list_s *node;
	char *position;

	for (index = 0; index < 10; index++)
	{
		node = nodeStartsWith(info->alias_list, info->arg_array[0], '=');
		if (!node)
			return (0);
		free(info->arg_array[0]);
		position = stringSearch(node->string, '=');
		if (!position)
			return (0);

		position = stringDuplicate(position + 1);
		if (!position)
			return (0);

		info->arg_array[0] = position;
	}

	return (1);
}

/**
 * replaceVars - This replaces variables in the tokenized string
 * @info: This is the argument struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVars(arg_u *info)
{
	int index = 0;
	list_s *node = NULL;
	char *value = NULL;

	for (index = 0; info->arg_array[index]; index++)
	{
		if (info->arg_array[index][0] != '$' || !info->arg_array[index][1])
			continue;
		if (!stringCompare(info->arg_array[index], "$?"))
		{
			replaceString(&(info->arg_array[index]),
					stringDuplicate(convertNumber(info->last_status, 10, 0)));
			continue;
		}
		if (!stringCompare(info->arg_array[index], "$$"))
		{
			replaceString(&(info->arg_array[index]),
					stringDuplicate(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env_list, &(info->arg_array[index][1]), '=');
		if (node)
		{
			value = stringSearch(node->string, '=');
			if (value)
				replaceString(&(info->arg_array[index]), stringDuplicate(value + 1));
			continue;
		}
		replaceString(&(info->arg_array[index]), stringDuplicate(""));
	}
	return (1);
}

/**
 * replaceString - This replaces string
 * @str: This is the address of old string
 * @var: This is the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **str, char *var)
{
	free(*str);
	*str = var;
	return (1);
}
