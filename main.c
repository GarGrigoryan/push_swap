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
	int		len, strategy, bench, start_idx;

	if (argc < 2)
		return (0);
	stack_a.top = NULL;
	stack_b.top = NULL;

	start_idx = flag_checker(argc, argv, &strategy, &bench);
	parse_arguments(argc, argv, &stack_a, start_idx);
	assign_indexes(&stack_a);
	
	init_ops(&ops);
	if (!ops)
	{
		free_stack(&stack_a); 
		return (1);
	}
	
	float disorder = compute_disorder(&stack_a);// sortirovki tokosy hakarak

	if (!is_sorted(&stack_a))
	{
		len = get_stack_length(&stack_a);
		
		if (len == 2)
			sa(&stack_a, ops);
		else if (len == 3)
			sort_3(&stack_a, ops);
		else if (strategy == 1 || (strategy == 4 && disorder < 0.2f))
			sort_n_square(&stack_a, &stack_b, ops); 
		else if (strategy == 3 || (strategy == 4 && disorder >= 0.5f))
			sort_radix(&stack_a, &stack_b, ops); 
		else
		{
			k_sort_distribution(&stack_a, &stack_b, ops); 
			push_back_to_a(&stack_a, &stack_b, ops);
		}
	}
	if (bench == 1)
	{
		int total_moves = ops->pa + ops->pb + ops->ra + ops->rb + ops->rr + 
						  ops->rra + ops->rrb + ops->rrr + ops->sa + ops->sb + ops->ss;
		
		write(2, "Benchmark: Total moves = ", 25);
		ft_putnbr_fd(total_moves, 2);
		write(2, "\n", 1);
	}

	free_stack(&stack_a);
	free(ops);
	return (0);
}