#include "header_shell_files.h"

/**
 * executeExit - exits the shell
 * @info: Structure containing potential arguments
 * Return: exits with a given exit control
 * (0) if arg.argv[0] != "exit"
 */
int executeExit(arg_u *info)
{
	int exitchck;

	if (info->arg_array[1])
	{
		exitchck = convertToIntWithErrorCheck(info->arg_array[1]);
		if (exitchck == -1)
		{
			info->last_status = 2;
			printError(info, "Illegal number: ");
			printErrorMessage_O(info->arg_array[1]);
			writeErrorChar('\n');
			return (1);
		}
		info->exit_error = convertToIntWithErrorCheck(info->arg_array[1]);
		return (-2);
	}
	info->exit_error = -1;
	return (-2);
}

/**
 * executeCd - changes the current directory of the process
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int executeCd(arg_u *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		printString("TODO: >>getcwd failure emsg here<<\n");
	if (!info->arg_array[1])
	{
		dir = getEnvironmentVariable(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = getEnvironmentVariable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (stringCompare(info->arg_array[1], "-") == 0)
	{
		if (!getEnvironmentVariable(info, "OLDPWD="))
		{
			printString(s);
			printCharacter('\n');
			return (1);
		}
		printString(getEnvironmentVariable(info, "OLDPWD=")), printCharacter('\n');
		chdir_ret = chdir((dir = getEnvironmentVariable(info, "OLDPWD="))
				? dir : "/");
	}
	else
		chdir_ret = chdir(info->arg_array[1]);
	if (chdir_ret == -1)
	{
		printError(info, "can't cd to ");
		printErrorMessage_O(info->arg_array[1]), writeErrorChar('\n');
	}
	else
	{
		setEnvironmentVariable(info, "OLDPWD", getEnvironmentVariable(info, "PWD="));
		setEnvironmentVariable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * executeHelp - changes the current directory of the process
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int executeHelp(arg_u *info)
{
	char **arg_array;

	arg_array = info->arg_array;
	printString("help call works. Function not yet implemented \n");
	if (0)
		printString(*arg_array);
	return (0);
}
