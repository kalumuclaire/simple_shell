#include "shell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * _pathcheck - Determine whether the current directory needs to be added
 * @path: environment variables for the path
 *
 * Return: Reference to new PATH’s address.
 *
 */

char *_pathcheck(char *path)
{
	char *npath;
	int c, a, nsize, count = 0;

	for (c = 0; path[c]; c++)
	{

		if (path[c] == '=' && path[c + 1] == ':')
			count++;
		if (path[c] == ':' && path[c + 1] == ':')
			count++;
		if (path[c] == ':' && path[c + 1] == '\0')
			count++;
	}
	if (count == 0)
		return (0);
	nsize = _strlen(path) + 1 + count;
	npath = malloc(sizeof(char) * nsize);

	for (c = 0, a = 0; c < nsize; c++, a++)
	{
		if (path[a] == '=' && path[a + 1] == ':')
		{
			npath[c] = path[a], npath[c + 1] = '.', c++;
			continue;
		}
		if (path[a] == ':' && path[a + 1] == ':')
		{
			npath[c] = path[a], npath[c + 1] = '.', c++;
			continue;
		}
		if (path[a] == ':' && path[a + 1] == '\0')
		{
			npath[c] = path[a], npath[c + 1] = '.', c++;
			continue;
		}
		npath[c] = path[a];
	}
	free(path);
	return (npath);
}
/**
 * _path - It looks for a cmd inside PATH.
 * @cmd: PATH environment variable string
 * @env: present env
 * @shpack: shell information array
 *
 * Return: Reference to the location of cmd by itself or in path.
 *
 */

char *_path(char *cmd, char **env, hshpack *shpack)
{
	char *path, *path2;
	struct stat st;
	char *token, *concat, *concat2, *pathcheck, *delim = ":=";
	int c;

	for (c = 0; cmd[c]; c++)
		if (cmd[c] == '/')
		{
			if (stat(cmd, &st) == 0)
				return (concat = str_concat(cmd, '\0'));
			else
				return (0);
		}

	path2 = _getenv("PATH", env);
	(void) shpack;
	if (!path2)
		return (0);
	path = _strdup(path2);
	pathcheck = _pathcheck(path);
	if (pathcheck)
		path = pathcheck;
	token = _strtok(path, delim);
	for (token = _strtok(0, delim); token; token = _strtok(0, delim))
	{
		concat = str_concat(token, "/");
		concat2 = str_concat(concat, cmd);
		free(concat);
		if (stat(concat2, &st) == 0)
		{
			/*Found the command in PATH*/
			free(path);
			return (concat2);
		}
		free(concat2);
	}

	free(path);
	return (0);
}
