/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garik <garik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:57:37 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/11 02:07:19 by garik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>
#include <unistd.h>

static void	rrev(t_stack *stack)
{
	t_node	*prev;
	t_node	*last;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	prev = NULL;
	last = stack->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = stack->top;
	stack->top = last;
}

void	rra(t_stack *a, t_ops *ops)
{
	rrev(a);
	ops->rra++;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b, t_ops *ops)
{
	rrev(b);
	ops->rrb++;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b, t_ops *ops)
{
	rrev(a);
	rrev(b);
	ops->rrr++;
	write(1, "rrr\n", 4);
}
