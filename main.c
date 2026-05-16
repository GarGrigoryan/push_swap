/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsezaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:32:32 by arsezaka          #+#    #+#             */
/*   Updated: 2026/03/16 22:32:04 by arsezaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	sort_dispatch(t_stack *a, t_stack *b, t_ops *ops)
{
	if (ops->len == 2)
		sa(a, ops);
	else if (ops->len == 3)
		sort_3(a, ops);
	else if (ops->len <= 5)
		sort_5(a, b, ops);
	else if (ops->strategy == 1
		|| (ops->strategy == 4 && ops->disorder < 0.2f))
		sort_n_square(a, b, ops);
	else if (ops->strategy == 3
		|| (ops->strategy == 4 && ops->disorder >= 0.5f && ops->len > 500))
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

	stack_a.top = NULL;
	stack_b.top = NULL;
	init_ops(&ops);
	if (!ops)
		return (free_stack(&stack_a));
	parse_arguments(argc, argv, &stack_a, flag_checker(argc, argv, ops));
	assign_indexes(&stack_a);
	ops->len = get_stack_length(&stack_a);
	ops->disorder = compute_disorder(&stack_a);
	if (!is_sorted(&stack_a))
		sort_dispatch(&stack_a, &stack_b, ops);
	if (ops->bench)
		print_bench(ops);
	if (ops->count_only)
		print_count(ops);
	free_stack(&stack_a);
	free_stack(&stack_b);
	free(ops);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	run(argc, argv);
	return (0);
}
