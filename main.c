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

static void	sort_dispatch(t_stack *a, t_stack *b, t_ops *ops,
				int len, int strategy, float disorder)
{
	if (len == 2)
		sa(a, ops);
	else if (len == 3)
		sort_3(a, ops);
	else if (len <= 5)
		sort_5(a, b, ops);
	else if (strategy == 1 || (strategy == 4 && disorder < 0.2f))
		sort_n_square(a, b, ops);
	else if (strategy == 3 || (strategy == 4 && disorder >= 0.5f))
		sort_radix(a, b, ops);
	else
	{
		k_sort_distribution(a, b, ops);
		push_back_to_a(a, b, ops);
	}
}

static void	run(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	t_ops	*ops;
	float	disorder;
	int		strategy;
	int		bench;
	int		len;
	int		start_idx;

	stack_a.top = NULL;
	stack_b.top = NULL;
	start_idx = flag_checker(argc, argv, &strategy, &bench);
	parse_arguments(argc, argv, &stack_a, start_idx);
	assign_indexes(&stack_a);
	init_ops(&ops);
	if (!ops)
		return (free_stack(&stack_a));
	disorder = compute_disorder(&stack_a);
	len = get_stack_length(&stack_a);
	if (!is_sorted(&stack_a))
		sort_dispatch(&stack_a, &stack_b, ops, len, strategy, disorder);
	if (bench == 1)
		print_bench(ops, disorder, strategy, len);
	free_stack(&stack_a);
	free(ops);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	run(argc, argv);
	return (0);
}
