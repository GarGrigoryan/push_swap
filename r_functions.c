/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garik <garik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:31:19 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/11 02:06:48 by garik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>
#include <unistd.h>

static void	r(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	first = stack->top;
	last = stack->top;
	while (last->next)
		last = last->next;
	stack->top = first->next;
	first->next = NULL;
	last->next = first;
}

void	ra(t_stack *a, t_ops *ops)
{
	r(a);
	ops->ra++;
	write(1, "ra\n", 3);
}

void	rb(t_stack *b, t_ops *ops)
{
	r(b);
	ops->rb++;
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b, t_ops *ops)
{
	r(a);
	r(b);
	ops->rr++;
	write(1, "rr\n", 3);
}
