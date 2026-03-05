/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:22:48 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/05 22:56:42 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!b || !b->top)
		return ;
	temp = b->top;
	b->top = b->top->next;
	temp->next = a->top;
	a->top = temp;
	write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!b || !b->top)
		return ;
	temp = a->top;
	a->top = a->top->next;
	temp->next = b->top;
	b->top = temp;
	write(1, "pb\n", 3);
}
