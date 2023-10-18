#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BSIZE 4
/**
 * _memset - uses constant bytes to load up memory.
 * @s: memory space
 * @b: unchanges byte b
 * @n: s indicates the first n bytes of memory
 *
 * Return: 1 if prosperous, on the occurrence of an error,
 * return -1, and errno is set properly.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int c;

	for (c = 0; c < n; c++)
		s[c] = b;
	return (s);
}
/**
 * _memcpy - duplicates memory
 * @dest: destination
 * @src: source
 * @n: the amount of memory to copy.
 *
 * Return: memory copied
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int c;

	for (c = 0; c < n; c++)
		dest[c] = src[c];
	return (dest);
}
/**
 * _realloc - utilize malloc and free to redistribute a memory block.
 * @ptr: Reference to change
 * @old_size: present size of memory
 * @new_size: memory capacity will now be available
 *
 * Return: a reference to reassigned memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *ptr2;

	if (old_size == new_size)
		return (ptr);

	if (ptr == NULL)
	{
		ptr2 = malloc(new_size);
		if (ptr2 == 0)
			return (0);
		free(ptr);
		return (ptr2);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (0);
	}

	ptr2 = malloc(new_size);

	if (ptr2 == 0)
		return (0);

	ptr2 = _memset(ptr2, '\0', new_size);

	_memcpy(ptr2, ptr, old_size);
	free(ptr);
	return (ptr2);
}
/**
 * _getline - From a stream of inputs, read a string or line.
 * @buffer: reference to the location where the stdin read will be stored
 * as a string
 * @bufsize: present buffer size, must be 0 initially
 * @fd: reading stream
 *
 * Return: Read characters count
 */
int _getline(char **buffer, size_t *bufsize, int fd)
{
	static char *buff;
	static size_t size;
	unsigned int len = 0, c = 0, sizeold;
	int p;

	if (*bufsize == 0)
		size = BSIZE;
	if (*buffer == 0)
	{
		buff = malloc(sizeof(char) * size);
		if (!buff)
			return (write(2, "Memory Error", 22), 0);
		*buffer = buff;
	}
	buff = _memset(buff, '\0', size);
	do {

		p = read(fd, buff + len, BSIZE);
		if (p >= 0)
			c = len, len += p;
		if (p == -1 || p == 0)
			return (-1);
		if  (len >= size)
		{
			sizeold = size, size += BSIZE;
			buff = _realloc(buff, sizeold, size);
			if (!buff)
				return (write(2, "Memory Error", 22), 0);
		}
		for (; c < len; c++)
		{
			if (buff[c] == '\n')
			{
				*buffer = buff, *bufsize = size;
				return (len);
			}
		}

	} while (1);
	return (len);
}
