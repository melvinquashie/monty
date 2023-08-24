#include "monty.h"
#include <stdio.h>

/**
 * main - main function for monty interpreter
 * @argc: arg count
 * @argv: arg vector list
 * Return: 0 on success or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	char opcode[6] = {0}, wrong[1024] = {0};
	ssize_t read;
	size_t len;
	stack_t *stack = NULL;
	int matches = 0;
	unsigned int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	global.fStream = NULL;
	global.fStream = fopen(argv[1], "r");
	if (global.fStream == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		fclose(global.fStream);
		exit(EXIT_FAILURE);
	}
	global.linePtr = NULL;
	while ((read = getline(&global.linePtr, &len, global.fStream)) != -1)
	{
		line_number++;
		if (!emptySpace())
		{
			matches = sscanf(global.linePtr, "%s%d%1s", opcode, &global.data, wrong);
			if (matches != 2 && strcmp(opcode, "push") == 0)
			{
				fprintf(stderr, "L%d: usage: push integer\n", line_number);
				exit_free(stack);
				exit(EXIT_FAILURE);
			}
			if (opcode[0] != '#')
				funcSelector(&stack, line_number, opcode);
		}
		free(global.linePtr);
		global.linePtr = NULL;
	}
	exit_free(stack);
	return (0);
}

/**
 * free_stack - free a stack with single ptr reference
 * @stack: pointer to a ll
 * Return: void
 */
void free_stack(stack_t *stack)
{
	stack_t *temp;

	while (stack != NULL)
	{
		temp = stack->next;
		free(stack);
		stack = temp;
	}
}

/**
 * exit_free - frees all possible allocs before exiting the program
 * @stack: ptr to a stack
 * Return: void
 */
void exit_free(stack_t *stack)
{
	fclose(global.fStream);
	if (global.linePtr != NULL)
		free(global.linePtr);
	free_stack(stack);
}

/**
 * emptySpace - check for whitespace
 *
 * Return: 1 if only whitespace 0 if not only whitespace
 */
int emptySpace(void)
{
	int i, j;
	char *ws = "\r\n\t ";

	for (i = 0; global.linePtr[i] != '\0'; i++)
		for (j = 0; ws[j] != '\0' && ws[j] != global.linePtr[i]; j++)
			if (ws[j] == '\n')
				return (0);
	return (1);
}
