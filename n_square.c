/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:16:38 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 01:28:40 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>

int	find_min(t_stack *a)
{
	int		min;
	int		min_index;
	t_node	*temp;

	if (!a || !a->top)
		return -1;
	temp = a->top;
	min = a->top->num;
	min_index = 0;
	while (temp->next)
	{
		if (min > temp->next->num)
		{
			min = temp->next->num;
			min_index = temp->next->index;
		}
		temp = temp->next;
	}
	return (min_index);
}

// void	sort_n_square(t_stack *a, t_stack *b)
// {

// }

int	main(void)
{
	t_stack	*stack;
	t_node	*node1;
	t_node	*node2;
	t_node	*node3;
	t_node	*node4;
	t_node	*temp;
	int		i = 0;

	node1 = malloc(sizeof(t_node));
	node2 = malloc(sizeof(t_node));
	node3 = malloc(sizeof(t_node));
	node4 = malloc(sizeof(t_node));
	stack = malloc(sizeof(t_stack));

	node1->num = -8;
	node2->num = -6;
	node3->num = -4;
	node4->num = -12;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	stack->top = node1;
	temp = stack->top;
	while(temp)
	{
		temp->index = i;
		i++;
		temp = temp->next;
	}
	print_stack(stack);
	//sa(stack);
	//printf("\n");
	//print_stack(stack);
	printf("\n%d", find_min(stack));
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(stack);
	return (0);
}
