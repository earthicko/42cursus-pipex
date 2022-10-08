/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/10 13:54:12 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <limits.h>

static int	count_words(char *str)
{
	int	n_words;

	n_words = 0;
	while (*str != '\0')
	{
		skip_space(&str, 0);
		if (*str != '\0')
			n_words++;
		skip_space(&str, 1);
	}
	return (n_words);
}

static char	*ft_strcpy_word(char *str)
{
	int		len_word;
	int		idx;
	char	*word;
	char	*end_of_word;

	end_of_word = str;
	skip_space(&end_of_word, 1);
	len_word = end_of_word - str;
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
	strip_quotes(&word);
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

char	**ft_split_args(char const *s)
{
	char	**strs;
	int		idx;
	int		n_words;
	char	*cursor;

	cursor = (char *)s;
	n_words = count_words(cursor);
	idx = 0;
	strs = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!strs)
		return (NULL);
	while (*cursor != '\0')
	{
		skip_space(&cursor, 0);
		if (*cursor != '\0')
		{
			strs[idx] = ft_strcpy_word(cursor);
			if (!strs[idx])
				return (abort_alloc(strs, idx - 1));
			idx++;
		}
		skip_space(&cursor, 1);
	}
	strs[idx] = 0;
	return (strs);
}
