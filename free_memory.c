#include "header_shell_files.h"

/**
 * freeBlock - This function frees a pointer
 * and makes the address NULL
 * @p: Pointer to the address to be freed
 *
 * Return: If freed, return 1, otherwise 0
 */
int freeBlock(void **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
