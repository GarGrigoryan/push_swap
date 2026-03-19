/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gargrigo <gargrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:28:04 by gargrigo          #+#    #+#             */
/*   Updated: 2026/03/06 17:29:11 by gargrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "push_swap.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

float compute_disorder(t_stack *stack_a){
	t_node *curr;
	t_node *cmp;

	double mistakes;
	double total_pairs;

	if(!stack_a || !stack_a->top || !stack_a->top->next)
		return(0.0f);
	
	mistakes = 0;
	total_pairs= 0;
	curr = stack_a->top;

		while(curr)
		{
			cmp = curr->next;
			while(cmp){
				total_pairs++;
				if(curr->num > cmp->num)
					mistakes++;
				cmp = cmp->next;
			}
			curr = curr->next;
		}
		return ((float)(mistakes / total_pairs));
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	num;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	c = (num % 10) + '0';
	write(fd, &c, 1);
}