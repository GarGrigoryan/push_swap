/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:16:32 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/16 22:25:01 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// function compute_disorder(stack a):
// mistakes = 0
// total_pairs = 0
// for i from 0 to size(a)-1:
// for j from i+1 to size(a)-1:
// total_pairs += 1
// if a[i] > a[j]:
// mistakes += 1
// return mistakes / total_pairs

float	compute_disorder(t_stack *stack)
{
	t_node	*a;
	t_node	*b;
	int		mistakes;
	int		total_pairs;

	if (!stack || !stack->top)
		return (0);
	mistakes = 0;
	total_pairs = 0;
	a = stack->top;
	while (a)
	{
		b = a->next;
		while (b)
		{
			total_pairs++;
			if (a->num > b->num)
				mistakes++;
			b = b->next;
		}
		a = a->next;
	}
	if (total_pairs == 0)
		return (0);
	return ((float)mistakes / total_pairs);
}
