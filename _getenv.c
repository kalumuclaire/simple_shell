#include <unistd.h>
#include "shell.h"

/**
 * _getenv - obtains an environmental number
 * @name: environmental number’s name.
 * @env: environment that is present
 *
 * Return: pointer to the environment’s value
 * or NULL if no match is found
 */
char *_getenv(const char *name, char **env)
{
	int c, a, check, l = 0;

	if (!env)
		return (NULL);

	while (name[l] != 0)
		l++;

	for (c = 0; env[c] != 0; c++)
	{
		for (check = 0, a = 0; a < l && env[c][a] != 0; a++)
			if (env[c][a] == name[a])
				check++;
		if (check == l && env[c][check] == '=')
			return (env[c]);
	}

	return (NULL);
}
