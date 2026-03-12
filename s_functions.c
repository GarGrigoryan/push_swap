/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:18:16 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/13 00:05:45 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static void	swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	first = stack->top;
	second = stack->top->next;
	first->next = second->next;
	second->next = first;
	stack->top = second;
}

void	sa(t_stack *a, t_ops *ops)
{
	swap(a);
	ops->sa++;
	write(1, "sa\n", 3);
}

void	sb(t_stack *b, t_ops *ops)
{
	swap(b);
	ops->sb++;
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b, t_ops *ops)
{
	swap(a);
	swap(b);
	ops->ss++;
	write(1, "ss\n", 3);
}
