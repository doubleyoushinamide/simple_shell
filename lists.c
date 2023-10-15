#include "header_shell_files.h"

/**
 * addNode - This function adds a node to beginning of list
 * @head: address of pointer to head node
 * @string: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */

list_s *addNode(list_s **head, const char *string, int number)
{
	list_s *newHead;

	if (!head)
		return (NULL);
	newHead = malloc(sizeof(list_s));
	if (!newHead)
		return (NULL);
	memorySet((void *)newHead, 0, sizeof(list_s));
	newHead->number = number;
	if (string)
	{
		newHead->string = stringDuplicate(string);
		if (!newHead->string)
		{
			free(newHead);
			return (NULL);
		}
	}
	newHead->next = *head;
	*head = newHead;
	return (newHead);
}

/**
 * addNodeEnd - This function adds a node to the end of the list
 * @head: address of pointer to head node
 * @string: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */

list_s *addNodeEnd(list_s **head, const char *string, int number)
{
	list_s *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_s));
	if (!newNode)
		return (NULL);
	memorySet((void *)newNode, 0, sizeof(list_s));
	newNode->number = number;
	if (string)
	{
		newNode->string = stringDuplicate(string);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * printListString - This function prints only the str element
 * @head: pointer to first node
 *
 * Return: size of list
 */

size_t printListString(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		printString(head->string ? head->string : "(nil)");
		printString("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * deleteNodeAtIndex - This function deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int deleteNodeAtIndex(list_s **head, unsigned int index)
{
	list_s *nodes, *prevNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nodes = *head;
		*head = (*head)->next;
		free(nodes->string);
		free(nodes);
		return (1);
	}
	nodes = *head;
	while (nodes)
	{
		if (i == index)
		{
			prevNode->next = nodes->next;
			free(nodes->string);
			free(nodes);
			return (1);
		}
		i++;
		prevNode = nodes;
		nodes = nodes->next;
	}
	return (0);
}

/**
 * freeList - This function frees all nodes of a list
 * @head: this is the address of pointer to head node
 *
 * Return: void
 */

void freeList(list_s **head)
{
	list_s *nodes, *nextNode, *head_O;

	if (!head || !*head)
		return;
	head_O = *head;
	nodes = head_O;
	while (nodes)
	{
		nextNode = nodes->next;
		free(nodes->string);
		free(nodes);
		nodes = nextNode;
	}
	*head = NULL;
}
