/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:16:17 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/05 22:19:33 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

void	print_stack(t_stack *stack)
{
	t_node *temp;
	if (!stack)
		return ;
	temp = stack->top;
	while (temp)
	{
		printf("%d\n", temp->num);
		temp = temp->next;
	}
}

// int	main(void)
// {
// 	t_stack	*stack;
// 	t_node *node1;
// 	t_node *node2;
// 	t_node *node3;

// 	node1 = malloc(sizeof(t_node));
// 	// node2 = malloc(sizeof(t_node));
// 	// node3 = malloc(sizeof(t_node));
// 	stack = malloc(sizeof(t_stack));

// 	node1->num = 10;
// 	// node2->num = 12;
// 	// node3->num = 24;

// 	// node1->next = node2;
// 	// node2->next = node3;
// 	stack->top = node1;
// 	print_stack(stack);
// 	sa(stack);
// 	printf("\n");
// 	print_stack(stack);
// 	return (0);
// }
