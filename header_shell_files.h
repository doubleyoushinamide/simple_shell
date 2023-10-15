#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>


/**********Defining the constants**********/

/* Command chaining constants */
#define COMMAND_CHAIN	3
#define AND_CONDITION	2
#define NORMAL		0
#define OR_CONDITION	1

/* Constants for read/write buffers */
#define BUFFER_SIZE_READ    1024
#define BUFFER_SIZE_WRITE   1024
#define BUFFER_FLUSH    -1

/* Configuration for shell history */
#define HISTORY_FILE_NAME	".custom_shell_history"
#define HISTORY_MAX_ENTRIES	4096

/* Flags for system functions */
#define SYSTEM_USE_GETLINE	0 /* Set to 1 if using system getline() */
#define SYSTEM_USE_STRTOK	0 /* Set to 1 if using system strtok() */

/* Configuration for number conversion */
#define NUMBER_CONVERT_LOWERCASE	1 /* Convert numbers to lowercase */
#define NUMBER_CONVERT_UNSIGNED		2 /* Convert numbers as unsigned */


/***********Defining the global environ variable**********/

extern char **environ;


/**********Defining structs**********/

/**
 * struct my_list - This is a singly linked list
 * @number: This is a number field
 * @string: This is a string
 * @next: This points to the next node
 */
typedef struct my_list
{
	int number;
	char *string;
	struct my_list *next;
} list_s;

/**
 * struct pass_arg - This contains pseudo-arguments to be passed
 * allows uniform prototype for the function struct pointer
 * @arg_str: This contains string arguments generated from getline
 * @arg_array:This is an array of strings generated from arg_str
 * @cmd_path: This is the string path for the current command
 * @arg_count: This is the argument count
 * @error_count: This counts the errors
 * @exit_error: This is the error code for exit()
 * @count_flag: Count this line of input, if on
 * @filename: This is the filename of the program
 * @env_list: linked list, a local copy of environ
 * @history_list: This is the history node
 * @alias_list: This is the alias node
 * @environ: This is a custom modified copy of environ
 * @env_changed: This is on if environ was changed
 * @last_status: This is the return status of the last executed command
 * @cmd_buffer: This is the address of the pointer to cmd_buffer
 * @cmd_buffer_type: CMD_type (||, &&, ;)
 * @read_fd: The file descriptor from which to read line input
 * @history_count: This is the number count of the history line
 */

typedef struct pass_arg
{
	char *arg_str;
	char **arg_array;
	char *cmd_path;
	int arg_count;
	unsigned int error_count;
	int exit_error;
	int count_flag;
	char *filename;
	list_s *env_list;
	list_s *history_list;
	list_s *alias_list;
	char **environ;
	int env_changed;
	int last_status;
	char **cmd_buffer;
	int cmd_buffer_type;
	int read_fd;
	int history_count;
} arg_u;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct built_in - This contains a builtin string & other related functions
 * @type: This is the built-in ccommand flag
 * @func: This is a function
 */

typedef struct built_in
{
	char *type;
	int (*func)(arg_u *);
} built_in_tab;

/* File: simple_shloop.c */
void executeShell(arg_u *, char **);
int hsh(arg_u *, char **);
int find_builtin(arg_u *);
void find_cmd(arg_u *);
void fork_cmd(arg_u *);

/* File: shell_parser.c */

int isCmd(arg_u *, char *);
char *dupChars(char *, int, int);
char *findPath(arg_u *, char *, char *);


/* File: error_handling.c */

void printErrorMessage_O(char *);
int writeErrorChar(char);
int writeCharToFileDescriptor(char c, int fd);
int writeStringToFileDescriptor(char *str, int fd);

/* File: string_operations.c */

int stringLength(char *);
int stringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *stringConcatenate_O(char *, char *);

/* File: string_operations1.c */

char *stringCopy_O(char *, char *);
char *stringDuplicate(const char *);
void printString(char *);
int printCharacter(char);

/* File: exit_operations.c */

char *stringCopy(char *, char *, int);
char *stringConcatenate(char *, char *, int);
char *stringSearch(char *, char);

/* File: tokens.c */

char **tokenizeString(char *, char *);
char **tokenizeStringByChar(char *, char);

/* File: re_alloc.c */

char *memorySet(char *, char, unsigned int);
void freeMemory(char **);
void *customRealloc(void *, unsigned int, unsigned int);

/* File: free_memory.c */

int freeBlock(void **);

/* File: atoi.c */

int interactive(arg_u *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int convertToInt(char *);

/* File: errors.c */

int convertToIntWithErrorCheck(char *);
void printError(arg_u *, char *);
int printDigit(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);

/* File: built_in.c */

int executeExit(arg_u *);
int executeCd(arg_u *);
int executeHelp(arg_u *);

/* File: built_in1.c */

int executeHistory(arg_u *);
int executeAlias(arg_u *);

/* File: getLine.c */

ssize_t cusInputBuf(arg_u *, char **, size_t *);
ssize_t getInput(arg_u *);
ssize_t readBuffer(arg_u *, char *, size_t *);
int customGetLine(arg_u *, char **, size_t *);
void sigintHandler(int);

/* File: getInfo.c */

void clearInfo(arg_u *);
void setInfo(arg_u *, char **);
void freeInfo(arg_u *, int);

/* File: environ.c */

char *getEnvironmentVariable(arg_u *, const char *);
int executeEnvCommand(arg_u *);
int executeSetenvCommand(arg_u *);
int executeUnsetenvCommand(arg_u *);
int populateEnvironmentList(arg_u *);

/* File: getEnv.c */

char **getEnvironmentVariables(arg_u *);
int unsetEnvironmentVariable(arg_u *, char *);
int setEnvironmentVariable(arg_u *, char *, char *);

/* File: get_history.c */

char *getHistoryFile(arg_u *info);
int writeHistory(arg_u *info);
int readHistory(arg_u *info);
int buildHistoryList(arg_u *info, char *buffer, int lineCount);
int renumberHistory(arg_u *info);

/* File: lists.c */

list_s *addNode(list_s **, const char *, int);
list_s *addNodeEnd(list_s **, const char *, int);
size_t printListString(const list_s *);
int deleteNodeAtIndex(list_s **, unsigned int);
void freeList(list_s **);

/* File: lists1.c */

size_t listLength(const list_s *);
char **listToStrings(list_s *);
size_t printList(const list_s *);
list_s *nodeStartsWith(list_s *, char *, char);
ssize_t getNodeIndex(list_s *, list_s *);

/* File: varb.c */

int isChain(arg_u *, char *, size_t *);
void checkChain(arg_u *, char *, size_t *, size_t, size_t);
int replaceAlias(arg_u *);
int replaceVars(arg_u *);
int replaceString(char **, char *);

#endif /* SHELL_H */
