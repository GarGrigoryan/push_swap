/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsezaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:32:32 by arsezaka          #+#    #+#             */
/*   Updated: 2026/03/16 22:32:04 by arsezaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_errors(long result, int sign, char c, int *error)
{
	if (c != '\0')
	{
		*error = 2;
		return (0);
	}
	if (result * sign > INT_MAX || result * sign < INT_MIN)
	{
		*error = 3;
		return (0);
	}
	return ((int)(result * sign));
}

int	ft_atoi(const char *str, int *error)
{
	unsigned int	i;
	int				sign;
	long			result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
	{
		*error = 1;
		return (0);
	}
	while (str[i] >= 48 && str[i] <= 57)
		result = result * 10 + (str[i++] - 48);
	return (check_errors(result, sign, str[i], error));
}

int	flag_checker(int argc, char **argv, t_ops *ops)
{
	int	i;

	ops->strategy = 4;
	ops->bench = 0;
	ops->count_only = 0;
	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] == '-')
	{
		if (!ft_strncmp(argv[i], "--simple", 9))
			ops->strategy = 1;
		else if (!ft_strncmp(argv[i], "--medium", 9))
			ops->strategy = 2;
		else if (!ft_strncmp(argv[i], "--complex", 10))
			ops->strategy = 3;
		else if (!ft_strncmp(argv[i], "--adaptive", 11))
			ops->strategy = 4;
		else if (!ft_strncmp(argv[i], "--bench", 8))
			ops->bench = 1;
		else if (!ft_strncmp(argv[i], "--count-only", 13))
			ops->count_only = 1;
		else
			break ;
		i++;
	}
	return (i);
}

static void	parse_split(char **str_2d, t_stack *stack_a)
{
	int	j;
	int	num;
	int	error;

	j = 0;
	while (str_2d && str_2d[j])
	{
		error = 0;
		num = ft_atoi(str_2d[j], &error);
		if (error || is_duplicate(stack_a->top, num))
		{
			free_all_mem(str_2d);
			free_stack(stack_a);
			write(2, "Error\n", 6);
			exit(1);
		}
		stack_add_back(stack_a, stack_new(num));
		j++;
	}
}

void	parse_arguments(int argc, char **argv, t_stack *stack_a, int start)
{
	int		i;
	char	**str_2d;

	if (argc < 2)
		return ;
	i = start;
	while (i < argc)
	{
		str_2d = ft_split(argv[i], ' ');
		if (!str_2d || !str_2d[0])
		{
			free_all_mem(str_2d);
			free_stack(stack_a);
			write(2, "Error\n", 6);
			exit(1);
		}
		parse_split(str_2d, stack_a);
		free_all_mem(str_2d);
		i++;
	}
}
