/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 03:02:34 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/13 00:05:04 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_ops(int min, int length)
{
	int	dst_to_end_min;

	dst_to_end_min = length - min;
	if (min < dst_to_end_min)
		return (min);
	else
		return (dst_to_end_min);
}

void	sort_3(t_stack *a, t_ops *ops)
{
	int	first;
	int	second;
	int	third;

	first = a->top->num;
	second = a->top->next->num;
	third = a->top->next->next->num;
	if (first > second && second < third && first < third)
		sa(a, ops);
	else if (first > second && second > third)
	{
		sa(a, ops);
		rra(a, ops);
	}
	else if (first > second && second < third && first > third)
		ra(a, ops);
	else if (first < second && second > third && first < third)
	{
		sa(a, ops);
		ra(a, ops);
	}
	else if (first < second && second > third && first > third)
		rra(a, ops);
}

void	sort_5(t_stack *a, t_stack *b, t_ops *ops)
{
	int	min_pos;
	int	len;

	len = get_stack_length(a);
	min_pos = find_min_index(a);
	if (min_pos <= len / 2)
		while (min_pos-- > 0)
			ra(a, ops);
	else
		while (min_pos++ < len)
			rra(a, ops);
	pb(a, b, ops);

	len = get_stack_length(a);
	min_pos = find_min_index(a);
	if (min_pos <= len / 2)
		while (min_pos-- > 0)
			ra(a, ops);
	else
		while (min_pos++ < len)
			rra(a, ops);
	pb(a, b, ops);

	sort_3(a, ops);
	pa(a, b, ops);
	pa(a, b, ops);
}