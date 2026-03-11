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

void	parse_arguments(int argc, char **argv, t_stack *stack_a);
int		ft_atoi(const char *str, int *error);
int		is_duplicate(t_node *stack, int num);
int		flag_checker(char **argv);
char	**free_all_mem(char **mem_seg);
void	free_stack(t_stack *stack);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

t_node	*stack_new(int num);
void	stack_add_back(t_stack *stack, t_node *new_node);

void	sa(t_stack *stack);
void	sb(t_stack *stack);
void	pb(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif