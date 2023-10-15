#include "header_shell_files.h"

/**
 * memorySet - This function fills the memory with a constant byte
 * @ptr: This is a pointer to the memory area
 * @value: This is the value of the byte to fill the memory with
 * @size: This is the number of bytes to be filled
 *
 * Return: returns a pointer to the memory area
 */
char *memorySet(char *ptr, char value, unsigned int size)
{
	unsigned int index;

	for (index = 0; index < size; index++)
		ptr[index] = value;
	return (ptr);
}

/**
 * freeMemory - This is a function that frees a block of memory
 * @ptr: This is a pointer to the memory block to be freed
 * Return: Doesn't return anything
 */
void freeMemory(char **ptr)
{
	char **b = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(b);
}

/**
 * customRealloc - This function is used to reallocate a block of memory
 * @ptr: This is a pointer to the previous allocated block
 * @oldSize: This is the size of the previous block in bytes
 * @newSize: This is the size of the new block in bytes
 *
 * Return: Returns a pointer to the reallocated memory block
 */

void *customRealloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	if (!ptr)
		return (malloc(newSize));

	if (!newSize)
		return (free(ptr), NULL);

	if (newSize == oldSize)
		return (ptr);

	newPtr = malloc(newSize);

	if (!newPtr)
		return (NULL);

	oldSize = (oldSize < newSize) ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)ptr)[oldSize];

	free(ptr);
	return (newPtr);
}
