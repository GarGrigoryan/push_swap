/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_square_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 03:02:34 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 03:22:50 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	find_min4_index(int a, int b, int c, int d)
{
	int	min;
	int	index;

	min = a;
	index = 0;
	if (b < min)
	{
		min = b;
		index = 1;
	}
	if (c < min)
	{
		min = c;
		index = 2;
	}
	if (d < min)
	{
		min = d;
		index = 3;
	}
	return (index);
}

int	find_min4(int a, int b, int c, int d)
{
	int min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	if (d < min)
		min = d;
	return (min);
}

int	find_min_ops(int max, int min, int length)
{
	int	minimum;
	int	dst_to_end_min;
	int	dst_to_end_max;

	dst_to_end_min = length - min;
	dst_to_end_max = length - max;
	minimum = find_min4(min, max, dst_to_end_min, dst_to_end_max);
	return (minimum);
}
