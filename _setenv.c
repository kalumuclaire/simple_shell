#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * free_doubpoint - releases a string array with double pointers,
 * must end in NULL
 * @p: double pointer
 *
 * Return: nil
 */
void free_doubpoint(char **p)
{
	int c, l = 0;

	while (p[l] != 0)
		l++;

	for (c = 0; c < l; c++)
	{
		free(p[c]);
	}
	free(p);
}
/**
 * _copydoublep - It replicates a string array, double pointer.
 *
 * @p: said double pointer
 * @old_size: P’s initial size
 * @new_size: copy size
 *
 * Return: malloc’s reference
 */
char **_copydoublep(char **p, int old_size, int new_size)
{
	char **copy;
	int c, size;

	if (!p && (old_size == new_size))
		return (NULL);

	if (new_size < old_size)
	{
		size = new_size;
		copy = malloc(sizeof(char *) * (size + 1));
	}
	else
	{
		size = old_size;
		copy = malloc(sizeof(char *) * (new_size + 1));
	}
	if (copy == 0)
		return (0);

	if (p)
		for (c = 0; c < size; c++)
		{
			copy[c] = _strdup(p[c]);
			if (copy[c] == 0)
			{
				c--;
				for (; c >= 0; c--)
					free(copy[c]);
				free(copy);
				return (0);
			}
		}

	/* Add Null in the end */
	copy[new_size] = '\0';

	return (copy);
}
/**
 * _strlendp - determines the measurement of a double pointer
 * which ends in NULL
 * @s: doubled pointer.
 *
 * Return: Length of doubled pointer
 *
 */
int _strlendp(char **s)
{
	int c = 0;

	if (!s)
		return (0);

	while (s[c] != NULL)
		c++;
	return (c);
}
/**
 * _setenv - generates or overrides an environment variable.
 *
 * @env: string of environment number
 * @variable: environment number set
 * @value: value to set
 * @shpack: shell information storage
 *
 * Return: 0 if success, -1 if error
 */
char **_setenv(char **env, char *variable, char *value, hshpack *shpack)
{
	int c, a, check, l = 0, lenv = 0;
	char *envjoin, *envjoin2, *copydup, **copy;

	if (_strlen(variable) == 0 || variable == 0)
		return (_error(3, shpack, 1), NULL);
	envjoin2 = str_concat(variable, "=");
	if (envjoin2 == 0)
		return (_error(3, shpack, 1), NULL);
	envjoin = str_concat(envjoin2, value), free(envjoin2);
	if (envjoin == 0)
		return (_error(3, shpack, 1), NULL);
	l = _strlen(variable), lenv = _strlendp(env);
	for (c = 0; env && env[c] != 0; c++)
	{
		for (check = 0, a = 0; a < l && env[c][a] != 0; a++)
		{
			if (variable[a] == '=')
				return (free(envjoin), _error(3, shpack, 2), NULL);
			if (env[c][a] == variable[a])
				check++;
		}
		if (check == l && env[c][check] == '=')
		{
			free(env[c]), copydup = _strdup(envjoin), free(envjoin);
			if (copydup == 0)
				return (_error(3, shpack, 1), NULL);
			return (env[c] = copydup, env);
		}
	}
	copy = _copydoublep(env, lenv, lenv + 1);
	if (env)
		free_doubpoint(env);
	if (copy == 0)
		return (free(envjoin), _error(3, shpack, 1), NULL);
	env = copy, copydup = _strdup(envjoin), free(envjoin);
	if (copydup == 0)
		return (_error(3, shpack, 1), NULL);
	return (env[lenv] = copydup, env);
}
