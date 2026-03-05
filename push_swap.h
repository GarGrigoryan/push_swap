/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:34:31 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/05 22:20:46 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_node
{
	struct s_node	*next;
	int				num;
}	t_node;

typedef struct s_list
{
	t_node	*top;
}	t_stack;

void	sa(t_stack *stack);
void	sb(t_stack *stack);

#endif
