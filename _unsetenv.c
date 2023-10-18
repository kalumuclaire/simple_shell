#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _copydoublepDel - dupes a string array, (double pointer)
 *
 * @p: double pointer to be duplicated.
 * @new_size: size of the dupe
 * @jump: value that should be left out in copy
 *
 * Return: malloc’s reference
 */
char **_copydoublepDel(char **p, int new_size, int jump)
{
	char **copy;
	int c, a, csize;

	csize = new_size;
	copy = malloc(sizeof(char *) * (csize + 1));
	if (copy == 0)
		return (0);

	for (c = 0, a = 0; a < csize; c++, a++)
	{
		if (c == jump)
			c++;
		copy[a] = _strdup(p[c]);
		if (copy[a] == 0)
		{
			a--;
			for (; a >= 0; a--)
				free(copy[a]);
			free(copy);
			return (0);
		}
	}

	copy[new_size] = '\0';

	return (copy);
}

/**
 * _unsetenv - disables a variable in the environmrnt
 *
 * @env: variety of environmental variables
 * @variable: environmental variable to exclude
 * @shpack: shell info store
 *
 * Return: 0 if successful, -1 on error occurence
 */
char **_unsetenv(char **env, char *variable, hshpack *shpack)
{
	int c, a, check, l = 0, lenv = 0, found = 0;
	char **copy;

	shpack->unsetnull[0] = 0;
	if (!env)
		return (write(2, "Environment is NULL\n", 20), NULL);
	if (_strlen(variable) == 0 || variable == 0)
		return (_error(3, shpack, 1), NULL);
	l = _strlen(variable), lenv = _strlendp(env);
	for (c = 0; env[c] != 0; c++)
	{
		for (check = 0, a = 0; a < l && env[c][a] != 0; a++)
		{
			if (variable[a] == '=')
				return (_error(3, shpack, 2), NULL);
			if (env[c][a] == variable[a])
				check++;
		}
		if (check == l && env[c][check] == '=')
		{
			/* Found env to erase */
			found = 1;
			if ((lenv - 1) != 0)
			{
				copy = _copydoublepDel(env, lenv - 1, c);
				if (copy == 0)
					return (_error(7, shpack, 1), NULL);
			}
			else
				shpack->unsetnull[0] = 1, copy = NULL;
			free_doubpoint(env), env = copy;
			return (env);
		}
	}
	if (found == 0)
		return (write(2, "VARIABLE not found\n", 19), NULL);
	return (env);
}
