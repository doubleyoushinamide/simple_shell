#include "header_shell_files.h"

/**
 * main - This collects user input
 * @ac: arg count ret
 * @av: arg vector ret
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	arg_u info = INFO_INIT;
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				printErrorMessage_O(av[0]);
				printErrorMessage_O(": 0: Can't open ");
				printErrorMessage_O(av[1]);
				writeErrorChar('\n');
				writeErrorChar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info.read_fd = fd;
	}
	populateEnvironmentList(&info);
	readHistory(&info);
	hsh(&info, av);
	return (EXIT_SUCCESS);
}
