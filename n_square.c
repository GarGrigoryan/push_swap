/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:16:38 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 20:15:36 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>

int	get_stack_length(t_stack *a)
{
	t_node	*temp;
	int		len;

	if (!a || !a->top)
		return (0);
	temp = a->top;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

int	find_min_index(t_stack *a)
{
	int		min;
	int		min_index;
	t_node	*temp;

	if (!a || !a->top)
		return -1;
	temp = a->top;
	min = a->top->num;
	while (temp->next)
	{
		if (min > temp->next->num)
			min = temp->next->num;
		temp = temp->next;
	}
	min_index = 0;
	temp = a->top;
	while (temp)
	{
		if (temp->num == min)
			return (min_index);
		temp = temp->next;
		min_index++;
	}
	return (min_index);
}

void	sort_n_square(t_stack *a, t_stack *b)
{
	int	min_index;
	int	stack_len;
	int	min_ops;
	int	count_functions[11];

	ft_memset(count_functions, 0, sizeof(count_functions));
	while (get_stack_length(a) > 3)
	{
		stack_len = get_stack_length(a);
		min_index = find_min_index(a);
		min_ops = find_min_ops(min_index, stack_len);
		if (min_index <= stack_len / 2)
			handle_min_ra(a, b, min_ops);
		else
			handle_min_rra(a, b, min_ops);
		//printf("\nmin_index = %d\n min_ops = %d", min_index, min_ops);
	}
	sort_3(a);
	while (b->top)
		pa(a, b);
	// printf("\ncount = %d\n", count_functions[3]);
}

int	main(void)
{
	t_stack	*stack;
	t_stack *b;
	t_node	*node1;
	t_node	*node2;
	t_node	*node3;
	t_node	*node4;
	t_node	*node5;
	t_node	*node6;
	t_node	*temp;
	//int		i = 0;

	node1 = malloc(sizeof(t_node));
	node2 = malloc(sizeof(t_node));
	node3 = malloc(sizeof(t_node));
	node4 = malloc(sizeof(t_node));
	node5 = malloc(sizeof(t_node));
	node6 = malloc(sizeof(t_node));
	stack = malloc(sizeof(t_stack));
	b = malloc(sizeof(t_stack));
	b->top = NULL;

	node1->num = 1248;
	node2->num = -10;
	node3->num = 6;
	node4->num = -5;
	node5->num = 1124;
	node6->num = 0;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	stack->top = node1;
	temp = stack->top;
	print_stack(stack);
	//sa(stack);
	//printf("\n");
	//print_stack(stack);
	// printf("\nmin_index = %d\n", find_min_index(stack));
	// printf("\nmax_index = %d\n", find_max_index(stack));
	// printf("\nlength = %d", get_stack_length(stack));
	// count_operations(find_max_index(stack), find_min_index(stack), get_stack_length(stack));
	//printf("max = %d", find_max(stack));
	sort_n_square(stack, b);
	print_stack(stack);

	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(stack);
	free(b);
	return (0);
}
