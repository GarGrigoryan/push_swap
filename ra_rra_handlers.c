/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_rra_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:32:01 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 18:52:51 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	handle_min_ra(t_stack *a, t_stack *b, int min_ops)
{
	int	i;

	i = 0;
	while (i++ < min_ops)
		ra(a);
	pb(a,b);
	return (min_ops);
}

int	handle_max_ra(t_stack *a, t_stack *b, int min_ops)
{
	int	i;

	i = 0;
	while (i++ < min_ops)
		ra(a);
	pb(a,b);
	rb(b);
	return (min_ops);
}

int	handle_min_rra(t_stack *a, t_stack *b, int min_ops)
{
	int	i;

	i = 0;
	while (i++ < min_ops)
		rra(a);
	pb(a,b);
	return (min_ops);
}

int	handle_max_rra(t_stack *a, t_stack *b, int min_ops)
{
	int	i;

	i = 0;
	while (i++ < min_ops)
		rra(a);
	pb(a,b);
	rb(b);
	return (min_ops);
}
