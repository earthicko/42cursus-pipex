/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/10 13:54:12 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static void	skip_separator(char **start, char c, int inverted)
{
	char	temp;

	if (inverted)
	{
		if (**start == '\'' || **start == '\"')
		{
			temp = **start;
			(*start)++;
			skip_separator(start, temp, inverted);
		}
		while (**start != '\0' && **start != c)
			(*start)++;
	}
	else
	{
		while (**start != '\0' && **start == c)
			(*start)++;
	}
}

static int	count_words(char *str, char sep)
{
	int	n_words;

	n_words = 0;
	while (*str != '\0')
	{
		skip_separator(&str, sep, 0);
		if (*str != '\0')
			n_words++;
		skip_separator(&str, sep, 1);
	}
	return (n_words);
}

static char	*ft_strcpy_word(char *str, char sep)
{
	int		len_word;
	int		idx;
	char	*word;
	char	*end_of_word;

	end_of_word = str;
	skip_separator(&end_of_word, sep, 1);
	len_word = end_of_word - str;
	if (*str == '\'' || *str == '\"')
	{
		str++;
		len_word -= 2;
	}
	idx = 0;
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (idx < len_word)
	{
		word[idx] = str[idx];
		idx++;
	}
	word[idx] = '\0';
	return (word);
}

static void	*abort_alloc(char **strs, int last_i)
{
	while (0 <= last_i)
	{
		free(strs[last_i]);
		last_i--;
	}
	free(strs);
	return (NULL);
}

char	**ft_split_escape(char const *s, char c)
{
	char	**strs;
	int		idx;
	int		n_words;
	char	*cursor;

	cursor = (char *)s;
	n_words = count_words(cursor, c);
	idx = 0;
	strs = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!strs)
		return (NULL);
	while (*cursor != '\0')
	{
		skip_separator(&cursor, c, 0);
		if (*cursor != '\0')
		{
			strs[idx] = ft_strcpy_word(cursor, c);
			if (!strs[idx])
				return (abort_alloc(strs, idx - 1));
			idx++;
		}
		skip_separator(&cursor, c, 1);
	}
	strs[idx] = 0;
	return (strs);
}
