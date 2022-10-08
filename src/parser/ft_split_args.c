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

static void	skip_space(char **str, int inverted);

static void	skip_until_quote(char **str, char quote)
{
	(*str)++;
	// ft_dprintf(2, "skip_until_quote: %c\n", quote);
	while (**str != '\0' && !(**str == quote && *(*str - 1) != '\\'))
	{
		// ft_dprintf(2, "skip_until_quote: meet %c\n", **str);
		(*str)++;
	}
	if (**str == quote)
		(*str)++;
	if (!ft_isspace(**str))
		skip_space(str, 1);
}

static void	skip_space(char **str, int inverted)
{
	if (inverted)
	{
		while (**str != '\0' && !ft_isspace(**str))
		{
			// ft_dprintf(2, "skip_space: meet %c\n", **str);
			if (ft_isquote(**str))
			{
				// ft_dprintf(2, "skip_space: begin quote skipping\n", **str);
				skip_until_quote(str, **str);
				return ;
			}
			(*str)++;
		}
	}
	else
	{
		while (**str != '\0' && ft_isspace(**str))
			(*str)++;
	}
}

// static void	skip_space(char **str, int inverted)
// {
// 	char	start;

// 	if (inverted)
// 	{
// 		start = **str;
// 		if (start == '\'' || start == '\"')
// 		{
// 			(*str)++;
// 			while (**str != '\0' && **str != start)
// 				(*str)++;
// 			if (**str == start)
// 				(*str)++;
// 		}
// 		else
// 			while (**str != '\0' && !ft_isspace(**str))
// 				(*str)++;
// 	}
// 	else
// 	{
// 		while (**str != '\0' && ft_isspace(**str))
// 			(*str)++;
// 	}
// }

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
	// ft_dprintf(2, "strcpy word [%s]\n", word);
	strip_quotes(&word);
	// ft_dprintf(2, "after strip [%s]\n", word);
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
		// ft_dprintf(2, "skip space, cursor at %c\n", *cursor);
		if (*cursor != '\0')
		{
			strs[idx] = ft_strcpy_word(cursor);
			if (!strs[idx])
				return (abort_alloc(strs, idx - 1));
			idx++;
		}
		skip_space(&cursor, 1);
		// ft_dprintf(2, "skip word, cursor at %c\n", *cursor);
	}
	strs[idx] = 0;
	return (strs);
}
