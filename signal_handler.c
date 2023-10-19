#include <unistd.h>
#include "shell.h"

/**
 * signal_handler - this handles ctrl + c in runtime
 * @x: shows the unused value, just for betty
 *
 * Return: shows No return
 */
void signal_handler(int x)
{
	(void) x;
	write(1, "\n$ ", 3);
}
/**
 * signal_handler2 - handles ctrl + c during cmd exec
 * @x: this shows unused value, just for betty
 *
 * Return:this shows No return
 */
void signal_handler2(int x)
{
	(void) x;
	write(1, "\n", 1);
}

