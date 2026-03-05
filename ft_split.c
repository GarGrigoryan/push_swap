/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsezaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:30:49 by arsezaka          #+#    #+#             */
/*   Updated: 2026/02/13 00:16:57 by arsezaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	**free_all_mem(char **mem_seg, size_t j)
{
	while (j--)
		free(mem_seg[j]);
	free(mem_seg);
	return (NULL);
}

static int	word_counter(char const *s, char c)
{
	int	in_word;
	int	i;
	int	word_count;

	in_word = 0;
	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			word_count++;
			in_word = 1;
		}
		else if (s[i] == c)
		{
			in_word = 0;
		}
		i++;
	}
	return (word_count);
}

static char	**filler(char const *s, char c, char **result)
{
	int	i;
	int	j;
	int	start_index;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		start_index = i;
		while (s[i] && s[i] != c)
			i++;
		result[j++] = ft_substr(s, start_index, i - start_index);
		if (!result[j - 1])
			return (free_all_mem(result, j - 1));
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc((word_counter(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	return (filler(s, c, result));
}
