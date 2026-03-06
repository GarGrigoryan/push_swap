/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 03:02:34 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 21:35:19 by gargrigo         ###   ########.fr       */
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

void	sort_3(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->top->num;
	second = a->top->next->num;
	third = a->top->next->next->num;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}
