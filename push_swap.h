/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garik <garik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:34:31 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/11 02:12:17 by garik            ###   ########.fr       */
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

typedef struct s_ops
{
	int pa;
	int pb;
	int ra;
	int rb;
	int rr;
	int rra;
	int rrb;
	int	rrr;
	int sa;
	int sb;
	int	ss;
}	t_ops;

void	sa(t_stack *stack, t_ops *ops);
void	sb(t_stack *stack, t_ops *ops);
void	ss(t_stack *a, t_stack *b, t_ops *ops);
void	pa(t_stack *a, t_stack *b, t_ops *ops);
void	pb(t_stack *a, t_stack *b, t_ops *ops);
void	ra(t_stack *a, t_ops *ops);
void	rb(t_stack *b, t_ops *ops);
void	rr(t_stack *a, t_stack *b, t_ops *ops);
void	rra(t_stack *a, t_ops *ops);
void	rrb(t_stack *b, t_ops *ops);
void	rrr(t_stack *a, t_stack *b, t_ops *ops);
void	print_stack(t_stack *stack);
int		find_min_ops(int min, int length);
int		find_min_position(int min, int length);
int		handle_min_ra(t_stack *a, t_stack *b, int min_ops, t_ops *ops);
int		handle_min_rra(t_stack *a, t_stack *b, int min_ops, t_ops *s_ops);
void	*ft_memset(void *s, int c, size_t n);
void	sort_3(t_stack *a, t_ops *ops);

#endif
