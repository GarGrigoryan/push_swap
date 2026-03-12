/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:16:38 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/12 23:59:06 by gargrigo         ###   ########.fr       */
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
		return (-1);
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

void	sort_n_square(t_stack *a, t_stack *b, t_ops *ops)
{
	int	min_index;
	int	stack_len;
	int	min_ops;

	while (get_stack_length(a) > 3)
	{
		stack_len = get_stack_length(a);
		min_index = find_min_index(a);
		min_ops = find_min_ops(min_index, stack_len);
		if (min_index <= stack_len / 2)
			handle_min_ra(a, b, min_ops, ops);
		else
			handle_min_rra(a, b, min_ops, ops);
	}
	sort_3(a, ops);
	while (b->top)
		pa(a, b, ops);
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
	t_ops	*ops;

	ops = malloc(sizeof(t_ops));
	ops->pa = 0;
	ops->pb = 0;
	ops->ra = 0;
	ops->rb = 0;
	ops->rr = 0;
	ops->rra = 0;
	ops->rrb = 0;
	ops->rrr = 0;
	ops->sa = 0;
	ops->sb = 0;
	ops->ss = 0;

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
	//print_stack(stack);
	//sa(stack);
	//printf("\n");
	//print_stack(stack);
	// printf("\nmin_index = %d\n", find_min_index(stack));
	// printf("\nmax_index = %d\n", find_max_index(stack));
	// printf("\nlength = %d", get_stack_length(stack));
	//count_operations(find_max_index(stack),
	//find_min_index(stack), get_stack_length(stack));
	//printf("max = %d", find_max(stack));
	sort_n_square(stack, b, ops);
	//print_stack(stack);
	//printf("pa: %d\npb: %d\nra: %d\nrb: %d\nrr: %d\nrra: %d\nrrb: %d\nrrr: %d\nsa: %d\nsb: %d\nss: %d\n", ops->pa, ops->pb, ops->ra, ops->rb, ops->rr, ops->rra, ops->rrb, ops->rrr, ops->sa, ops->sb, ops->ss);

	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(stack);
	free(b);
	free(ops);
	return (0);

}
