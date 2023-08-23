#include "monty.h"
/* For 'push', 'pall', 'pint' and 'add' */

/**
 * push - push a node onto the stack
 * @stack: stack
 * @line_number: line number in monty .m file
 * Return: void
 */
void push(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *tmp;

	tmp = malloc(sizeof(stack_t)); /* not freed */
	if (tmp == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		exit_free(*stack);
		exit(EXIT_FAILURE);
	}
	tmp->n = globes.data;
	tmp->prev = NULL;
	tmp->next = NULL;
	if (*stack != NULL)
	{
		tmp->next = *stack;
		(*stack)->prev = tmp;
	}
	*stack = tmp;
}
/**
 * pall - print all data in stack
 * @stack: stack
 * @line_number: line number in monty .m file
 * Return: void
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	(void) line_number;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}
/**
 * pint - print top int
 * @stack: stack
 * @line_number: line number in monty .m file
 * Return: void
 */
void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (tmp == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty", line_number);
		exit_free(*stack);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", tmp->n);
}

/**
 * add - add two nodes remove the top node and place sum in new
 * @stack: dll stack
 * @line_number: line num
 *
 * Return: void
 */
void add(stack_t **stack, unsigned int line_number)
{
	int a, b;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit_free(*stack);
		exit(EXIT_FAILURE);
	}
	a = (*stack)->n;
	b = (*stack)->next->n;
	*stack = (*stack)->next;
	free((*stack)->prev);
	(*stack)->prev = NULL;
	(*stack)->n = a + b;
}
