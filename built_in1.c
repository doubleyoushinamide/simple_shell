#include "header_shell_files.h"

/**
 * executeHistory - This function displays the
 * history list, one command by line, followed
 * with line numbers, starting at 0.
 *  @info: Struct
 *  Return: Always 0
 */
int executeHistory(arg_u *info)
{
	printList(info->history_list);
	return (0);
}

/**
 * unset_alias_list - This function sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int unset_alias_list(arg_u *info, char *str)
{
	char *p, c;
	int rete;

	p = stringSearch(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	rete = deleteNodeAtIndex(&(info->alias_list),
		getNodeIndex(info->alias_list, nodeStartsWith(info->alias_list, str, -1)));
	*p = c;
	return (rete);
}

/**
 * set_alias_list - This function sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias_list(arg_u *info, char *str)
{
	char *p;

	p = stringSearch(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_list(info, str));

	unset_alias_list(info, str);
	return (addNodeEnd(&(info->alias_list), str, 0) == NULL);
}

/**
 * print_alias_list - This function prints an alias string
 * @node: the node alias
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_list(list_s *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = stringSearch(node->string, '=');
		for (a = node->string; a <= p; a++)
		printCharacter(*a);
		printCharacter('\'');
		printString(p + 1);
		printString("'\n");
		return (0);
	}
	return (1);
}

/**
 * executeAlias - This function is used in place of the alias builtin
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int executeAlias(arg_u *info)
{
	int i = 0;
	char *p = NULL;
	list_s *node = NULL;

	if (info->arg_count == 1)
	{
		node = info->alias_list;
		while (node)
		{
			print_alias_list(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->arg_array[i]; i++)
	{
		p = stringSearch(info->arg_array[i], '=');
		if (p)
			set_alias_list(info, info->arg_array[i]);
		else
			print_alias_list(nodeStartsWith(info->alias_list, info->arg_array[i], '='));
	}

	return (0);
}
