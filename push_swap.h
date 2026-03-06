/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:34:31 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 20:08:12 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>

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
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);
void	print_stack(t_stack *stack);
int		find_min_ops(int min, int length);
int		find_min_position(int min, int length);
int		handle_min_ra(t_stack *a, t_stack *b, int min_ops);
int		handle_min_rra(t_stack *a, t_stack *b, int min_ops);
void	*ft_memset(void *s, int c, size_t n);
void	sort_3(t_stack *a);

#endif
