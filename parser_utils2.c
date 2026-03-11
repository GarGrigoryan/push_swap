/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsezaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:39:51 by arsezaka          #+#    #+#             */
/*   Updated: 2026/03/11 20:39:53 by arsezaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isdigit(int x)
{
	return (x > 47 && x < 58);
}

void	free_stack(t_stack *stack)
{
	t_node	*curr;
	t_node	*tmp;

	if (!stack || !stack->top)
		return ;
	curr = stack->top;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	stack->top = NULL;
}

int	is_duplicate(t_node *stack, int num)
{
	t_node	*curr;

	if (!stack)
		return (0);
	curr = stack;
	while (curr)
	{
		if (num == curr->num)
			return (1);
		curr = curr->next;
	}
	return (0);
}
