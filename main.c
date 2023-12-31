#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"
/**
 * main - shows Shell Program
 * @ac: this shows the count of input parameters to program
 * @av: this shows the parameters as input to program
 * @env: indicates unix environment
 *
 * Return: returns should only exit through shell inputs
 */
int main(int ac, char **av, char **env)
{
	size_t bufsize = 0;
	char **command, *pathCmd, *buffer = NULL;
	hshpack *shpack;
	int errn = 0, exnum = 0, relation = 0, run_able = 0, sizeEnv, enul = 0;
	ssize_t isBuiltIn;

	if (ac > 1 || av == NULL)
		write(2, "Please run with no arguments\n", 29), exit(127);
	signal(SIGINT, signal_handler);
	sizeEnv = _strlendp(env);
	env = _copydoublep(env, sizeEnv, sizeEnv);
	shpack = set_struct(av[0], &errn, &exnum, &relation, &run_able, &env, &enul);
	while (1)
	{
		command = NULL;
		command = checkInput(ac, av, &bufsize, &buffer, shpack);
		if (!command)
			continue;
		addCmd(shpack, buffer, command[0], command);
		isBuiltIn = built_ints(shpack);
		if (isBuiltIn == -1 || isBuiltIn == 1)
			continue;
		pathCmd = _path(command[0], env, shpack);
		addPathToCmd(shpack, pathCmd);
		if (!pathCmd)
		{
			free(command);
			shpack->errnum[0] += 1, _error(0, shpack, 127);
			continue;
		}
		else if (access(pathCmd, X_OK) == -1)
			_error(1, shpack, 126);
		else
			executeCmd(pathCmd, command, env, shpack);
		free(command);
		free(pathCmd);

	}
	free_doubpoint(*(shpack->envCpy)), free(shpack);
	return (0);
}
/**
 * set_struct - this only initializes shell struct
 * @argv0: this indicates the name of executable
 * @errn: this indicates the number of error message
 * @exnum: this indicates the exit number of shell
 * @relation: this indicates relation for logical operators
 * @run_able: this decides if cmd should be run
 * @env: shows the current environment
 * @unsetnull: indicates the check for setting environment to NULL
 *
 * Return:returns  Pointer to struct
 *
 */
hshpack *set_struct(char *argv0, int *errn, int *exnum,
		    int *relation, int *run_able, char ***env, int *unsetnull)
{
	hshpack *shellpack;

	shellpack = malloc(sizeof(struct Hshpack));
	if (shellpack == 0)
		return (write(2, "Memory Error", 22), NULL);
	shellpack->hshname = argv0;
	shellpack->buffer = NULL;
	shellpack->cmd = NULL;
	shellpack->options = NULL;
	shellpack->path = NULL;
	shellpack->errnum = errn;
	shellpack->exitnum = exnum;
	shellpack->relation = relation;
	shellpack->run_able = run_able;
	shellpack->envCpy = env;
	shellpack->unsetnull = unsetnull;

	return (shellpack);
}
/**
 * addCmd - it executes addition values to shell struct
 * @shpack: it indicates shell struct
 * @buffer:  its string is written after prompt
 * @command:  it ensures command written after prompt
 * @parameters:it shows the parameters of command
 *
 * Return: shows no return
 */
void addCmd(hshpack *shpack, char *buffer, char *command, char **parameters)
{
	shpack->buffer = buffer;
	shpack->cmd = command;
	shpack->options = parameters;
}

/**
 * addPathToCmd - this initializes path value of struct.
 * @shpack: indicates shell struct
 * @pathCmd: shows the path of cmd written after propmpt
 *
 * Return: shows No Return
 */
void addPathToCmd(hshpack *shpack, char *pathCmd)
{
	shpack->path = pathCmd;
}

