/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:16:38 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/13 00:16:22 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

