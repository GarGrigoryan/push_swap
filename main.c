#include "push_swap.h"

static int	is_sorted(t_stack *stack)
{
	t_node	*curr;

	if (!stack || !stack->top || !stack->top->next)
		return (1);
	curr = stack->top;
	while (curr->next)
	{
		if (curr->num > curr->next->num)
			return (0);
		curr = curr->next;
	}
	return (1);
}

static void	init_ops(t_ops **ops)
{
	*ops = malloc(sizeof(t_ops));
	if (*ops)
		ft_memset(*ops, 0, sizeof(t_ops));
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	t_ops	*ops;
	int		len;

	if (argc < 2)
		return (0);
	stack_a.top = NULL;
	stack_b.top = NULL;
	init_ops(&ops);
	if (!ops)
		return (1);
	parse_arguments(argc, argv, &stack_a);
	assign_indexes(&stack_a);
	
	if (!is_sorted(&stack_a))
	{
		len = get_stack_length(&stack_a);
		if (len == 2)
			sa(&stack_a, ops);
		else if (len == 3)
			sort_3(&stack_a, ops);
		else if (len <= 5)
			sort_n_square(&stack_a, &stack_b, ops);
		else{
			k_sort_distribution(&stack_a, &stack_b, ops);
			push_back_to_a(&stack_a, &stack_b, ops);
		}
	}

	free_stack(&stack_a);
	free(ops);
	return (0);
}