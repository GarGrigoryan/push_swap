/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_rra_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garik <garik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:32:01 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/11 02:14:24 by garik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	handle_min_ra(t_stack *a, t_stack *b, int min_ops, t_ops *ops)
{
	int	i;

	i = 0;
	while (i++ < min_ops)
		ra(a, ops);
	pb(a, b, ops);
	return (min_ops);
}

int	handle_min_rra(t_stack *a, t_stack *b, int min_ops, t_ops *ops)
{
	int	i;

	i = 0;
	while (i++ < min_ops)
		rra(a, ops);
	pb(a, b, ops);
	return (min_ops);
}
