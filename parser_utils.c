/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsezaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:22:24 by arsezaka          #+#    #+#             */
/*   Updated: 2026/03/11 20:39:37 by arsezaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*stack_new(int num)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->num = num;
    node->index = 0;
	node->next = NULL;
	return (node);
}

void	stack_add_back(t_stack *stack, t_node *new_node)
{
	t_node	*last;

	if (!stack || !new_node)
		return ;
	if (!stack->top)
	{
		stack->top = new_node;
		return ;
	}
	last = stack->top;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	assign_indexes(t_stack *stack_a)
{
	t_node	*curr;
	t_node	*cmp;
	int		index;

	if (!stack_a || !stack_a->top)
		return ;
	curr = stack_a->top;
	while (curr)
	{
		index = 0;
		cmp = stack_a->top;
		while (cmp)
		{
			if (curr->num > cmp->num)
				index++;
			cmp = cmp->next;
		}
		curr->index = index;
		curr = curr->next;
	}
}