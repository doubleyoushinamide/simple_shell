#include "header_shell_files.h"

/**
 * listLenght - This function determines the length of a linked list
 * @head: this is a pointer var to first node
 *
 * Return: size of list
 */

size_t listLenght(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * listToStrings- This function returns an array of strings of the list->str
 * @head: pointer into first node
 *
 * Return: array of strings
 */
char **listToStrings(list_s *head)
{
	list_s *node = head;
	size_t i = listLenght(head), j;
	char **strs;
	char *string;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(stringLength(node->string) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		string = stringCopy_O(string, node->string);
		strs[i] = string;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printList -This function prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t printList(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		printString(convertNumber(head->number, 10, 0));
		printCharacter(':');
		printCharacter(' ');
		printString(head->string ? head->string : "(nil)");
		printString("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * nodeStartsWith - This function returns node whose string starts with prefix
 * @head: pointer to list head
 * @string: string to match
 * @character: the next character after prefix to match
 *
 * Return: match node or null
 */
list_s *nodeStartsWith(list_s *head, char *string, char character)
{
	char *p = NULL;

	while (head)
	{
		p = startsWith(head->string, string);
		if (p && ((character == -1) || (*p == character)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * getNodeIndex -This function gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(list_s *head, list_s *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
