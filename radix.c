#include "push_swap.h"

static int	get_max_bits(int max_index)
{
	int	max_bits;

	max_bits = 0;
	while ((max_index >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

void	sort_radix(t_stack *a, t_stack *b, t_ops *ops)
{
	int	size;
	int	max_bits;
	int	i;
	int	j;

	size = get_stack_length(a);
	max_bits = get_max_bits(size - 1);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
	while (j++ < size)
		{
			
			if (((a->top->index >> i) & 1) == 1)
				ra(a, ops);
			else
				pb(a, b, ops);
		}
		while (b->top)
			pa(a, b, ops);
		i++;
	}
}