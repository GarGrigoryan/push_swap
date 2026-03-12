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

char	**free_all_mem(char **mem_seg)
{
	int i;

	i = 0;
	if (!mem_seg)
		return (NULL);
	while (mem_seg[i])
	{
		free(mem_seg[i]);
		i++;
	}
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
			in_word = 0;
		i++;
	}
	return (word_count);
}

static char	**filler(char const *s, char c, char **result)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		result[j] = ft_substr(s, start, i - start);
		if (!result[j])
			return (free_all_mem(result));
		j++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = word_counter(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	int i = 0;
	while (i <= words)
		result[i++] = NULL;
	return (filler(s, c, result));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (malloc(sizeof(char)));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}