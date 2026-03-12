/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:34:31 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/13 00:05:19 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_node
{
	struct s_node	*next;
	int				num;
}	t_node;

typedef struct s_stack
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

void	parse_arguments(int argc, char **argv, t_stack *stack_a);
int		ft_atoi(const char *str, int *error);
int		is_duplicate(t_node *stack, int num);
int		flag_checker(char **argv);
char	**free_all_mem(char **mem_seg);
void	free_stack(t_stack *stack);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int	ft_isdigit(int x);

t_node	*stack_new(int num);
void	stack_add_back(t_stack *stack, t_node *new_node);

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
void	sort_3(t_stack *a, t_ops *ops);

void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif