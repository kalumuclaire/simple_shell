#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * checkInput - this checks for input in after shell prompt
 * @ac: indicates count of main arguments
 * @av: indicates main arguments
 * @bufsize: shows the size of buffer in prompt
 * @buffer: indicates buffer in prompt
 * @shpack: shows struct of shell info
 *
 * Return: returns 1 on success..
 * On error, -1 is returned, and errno is set appropriately.
 */
char **checkInput(int ac, char **av, size_t *bufsize,
		   char **buffer, hshpack *shpack)
{
	ssize_t characters;
	char **command;
	int exitnum;

	if (ac == 1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		characters = getline(buffer, bufsize, stdin);

		if (characters == -1)
		{
			exitnum = shpack->exitnum[0];
			free(*buffer);
			if (*(shpack->envCpy))
				free_doubpoint(*(shpack->envCpy));
			free(shpack);
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			exit(exitnum);
		}
		if (**buffer == '#' || !characters || **buffer == '\n')
			return (NULL);
		*buffer = deleteComment(*buffer);
		command = getParameters(*buffer, shpack);
	}
	else
	{
		command = malloc(sizeof(char *) * (ac - 1));
		if (!command)
		{
			_error(7, shpack, 1);
			return (NULL);
		}

		command[ac - 1] = '\0';
		while (ac--)
			command[ac - 1] = av[ac];
	}
	return (command);
}

/**
 * deleteComment - this deletes a comment inside a command line
 *
 * @str: shows the string to operate
 *
 * Return: returns pointer to string
 *
 */
char *deleteComment(char *str)
{
	char *org = str;

	for (; str && *str; str++)
		if (*str == '#' && *(str - 1) == ' ')
		{
			*str = '\0';
			break;
		}

	return (org);
}
