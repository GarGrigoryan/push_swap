/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:16:38 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 03:35:10 by gargrigo         ###   ########.fr       */
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

int	find_max_index(t_stack *a)
{
	int		max;
	int		max_index;
	t_node	*temp;

	if (!a || !a->top)
		return (-1);
	temp = a->top;
	max = a->top->num;
	while (temp->next)
	{
		if (max < temp->next->num)
			max = temp->next->num;
		temp = temp->next;
	}
	max_index = 0;
	temp = a->top;
	while (temp)
	{
		if (temp->num == max)
			return (max_index);
		temp = temp->next;
		max_index++;
	}
	return (max_index);
}

int	find_min_position(int max, int min, int length)
{
	int	minimum;
	int	dst_to_end_min;
	int	dst_to_end_max;

	dst_to_end_min = length - min;
	dst_to_end_max = length - max;
	minimum = find_min4_index(min, max, dst_to_end_min, dst_to_end_max);
	return (minimum);
}

void	sort_n_square(t_stack *a, t_stack *b)
{
	int	min_index;
	int	max_index;
	int	min_pos;
	int	min_ops;

	min_index = find_min_index(a);
	max_index = find_max_index(a);
	min_pos = find_min_position(max_index, min_index, get_stack_length(a));
	min_ops = find_min_ops(max_index, min_index, get_stack_length(a));
	//printf("\nmin_index = %d\nmax_index = %d\n min_pos = %d\nmin_ops = %d", min_index, max_index, min_pos, min_ops);
	if (min_pos == 0)
		handle_min(a, min_ops);
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
	int		i = 0;

	node1 = malloc(sizeof(t_node));
	node2 = malloc(sizeof(t_node));
	node3 = malloc(sizeof(t_node));
	node4 = malloc(sizeof(t_node));
	node5 = malloc(sizeof(t_node));
	node6 = malloc(sizeof(t_node));
	stack = malloc(sizeof(t_stack));
	b = malloc(sizeof(t_stack));


	node1->num = 8;
	node2->num = -1;
	node3->num = 37;
	node4->num = 12;
	node5->num = 0;
	node6->num = 3;

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


	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(stack);
	return (0);
}
