/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:16:17 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 01:22:05 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

void	print_stack(t_stack *stack)
{
	t_node *temp;
	if (!stack || !stack->top)
		return ;
	temp = stack->top;
	while (temp)
	{
		printf("%d\n", temp->num);
		temp = temp->next;
	}
}
