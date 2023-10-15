#include "header_shell_files.h"

/**
 * executeShell - Executes the shell loop.
 *
 * @info: The argument struct.
 * @av: The command-line arguments.
 * Return: nothing
 */
void executeShell(arg_u *info, char **av)
{
	ssize_t r = 0;
	int builtInRet = 0;

	while (r != -1 && builtInRet != -2)
	{
		clearInfo(info);
		if (interactive(info))
			printString("$ ");
		writeErrorChar(BUFFER_FLUSH);
		r = getInput(info);
		if (r != -1)
		{
			setInfo(info, av);
			builtInRet = find_builtin(info);
			if (builtInRet == -1)
				find_cmd(info);
		}
		else if (interactive(info))
		{
			printCharacter('\n');
		}
		freeInfo(info, 0);
	}

	writeHistory(info);

	if (!interactive(info) && info->last_status)
		exit(info->last_status);
	if (builtInRet == -2)
	{
		if (info->exit_error == -1)
			exit(info->last_status);
		exit(info->exit_error);
	}
}

/**
 * hsh - main shell loop
 * @info: the parameter & return arg struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(arg_u *info, char **av)
{
	FILE *file = NULL;

	if (av[1])
	{
		file = fopen(av[1], "r");
		if (file == NULL)
		{
			perror("Error");
			return (1);
		}
		info->read_fd = fileno(file);
	}

	executeShell(info, av);

	fclose(file);

	return (0);
}

/**
 * find_builtin - This function finds a builtin command
 * @info: This is the argument struct
 *
 * Return:	Returns the following -
 *		-1 if builtin command not found
 *		0 if builtin command executed successfully
 *		1 if builtin command found but not successful
 *		-2 if builtin command signals exit()
 */
int find_builtin(arg_u *info)
{
	int i, built_inRet = -1;
	built_in_tab builtintbl[] = {
		{"exit", executeExit},
		{"env", executeEnvCommand},
		{"help", executeHelp},
		{"history", executeHistory},
		{"setenv", executeSetenvCommand},
		{"unsetenv", executeUnsetenvCommand},
		{"cd", executeCd},
		{"alias", executeAlias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (stringCompare(info->arg_array[0], builtintbl[i].type) == 0)
		{
			info->error_count++;
			built_inRet = builtintbl[i].func(info);
			break;
		}
	return (built_inRet);
}

/**
 * find_cmd - This function finds and executes the command
 * @info: Argument structure
 *
 * Return: nothing
 */
void find_cmd(arg_u *info)
{
	char *path = NULL;
	int i, k;
	int should_execute = 1;

	info->cmd_path = info->arg_array[0];
	if (info->count_flag == 1)
	{
		info->error_count++;
		info->count_flag = 0;
	}
	for (i = 0, k = 0; info->arg_str[i]; i++)
		if (!isDelimiter(info->arg_str[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findPath(info, getEnvironmentVariable(info, "PATH="),
			info->arg_array[0]);
	if (path)
	{
		info->cmd_path = path;
		if (should_execute)
			fork_cmd(info);
		return;
	}

	if ((interactive(info) || getEnvironmentVariable(info, "PATH=")
				|| info->arg_array[0][0] == '/')
			&& isCmd(info, info->arg_array[0]))
	{
		if (should_execute)
			fork_cmd(info);
		return;
	}

	if (*(info->arg_str) != '\n')
	{
		info->last_status = 127;
		printError(info, "not found\n");
	}
}


/**
 * fork_cmd - This function forks an exec thread to run cmd
 * @info: This is the argument struct
 *
 * Return: Returns nothing
 */
void fork_cmd(arg_u *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (stringCompare(info->arg_array[0], "exit") == 0)
		{
			executeExit(info);
			freeInfo(info, 1);
			_exit(info->exit_error);
		}

		if (execve(info->cmd_path,
		info->arg_array, getEnvironmentVariables(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
			{
				perror("Permission denied");
				_exit(126);
			}
			perror("Exec error");
			_exit(1);
		}
	}
	else
	{
		wait(&(info->last_status));
		if (WIFEXITED(info->last_status))
		{
			info->last_status = WEXITSTATUS(info->last_status);
			if (info->last_status == 126)
				perror("Permission denied");
		}
	}
}
