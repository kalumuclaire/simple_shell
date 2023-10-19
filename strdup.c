#include <stdlib.h>
#include "shell.h"

/**
 * _strcpy - allows to copy a source input onto designated input
 * @dest: shows the target where the stored input is
 * @src: allows to source to copy from
 *
 *
 * Return: returns destination address
 * On error: returns -1 inapropiate entry
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; *(src + i) != '\0'; i++)
		*(dest + i) = *(src + i);

	*(dest + i) = *(src + i); /* adding '\0' character */

	return (dest);
}

/**
 * _strlen - this function returns the length of a string
 * @s: represents the string address
 *
 *
 * Return: returns nothing
 * On error: returns -1 inappropriate entry
 */

int _strlen(char *s)
{
	return ((!*s) ? 0 : 1 + _strlen(s + 1));
}

/**
 * _strdup - this function returns a pointer to a newly allocated space
 * in memory, which contains a copy of the string given as a parameter
 * @str: shows source to copy
 *
 *
 * Return: returns the address where the stored result is
 * On error: returns -1 inapropiate entry
 */

char *_strdup(char *str)
{
	char *arr;

	if (!str)
		return (NULL);

	arr = malloc((_strlen(str) * sizeof(*arr)) + 1);

	if (!arr)
		return (NULL);

	_strcpy(arr, str);

	return (arr);
}
