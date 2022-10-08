/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/10 13:54:12 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	strip_quotes(char **p_str)
{
	size_t	len;
	char	*new;

	if (!(*p_str))
		return ;
	len = ft_strlen(*p_str);
	if ((*p_str)[0] == (*p_str)[len - 1] && ft_isquote((*p_str)[0]))
	{
		new = ft_substr(*p_str, 1, len - 2);
		free(*p_str);
		*p_str = new;
	}
}

static size_t	count_escapes(char *str)
{
	size_t	i;
	size_t	len;
	size_t	n_escape;

	len = ft_strlen(str);
	n_escape = 0;
	i = 1;
	while (i < len)
	{
		if (ft_isquote_escape(str + i))
			n_escape++;
		i++;
	}
	return (n_escape);
}

static void	strcpy_without_escape(char *from, char *to, size_t new_len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < new_len)
	{
		if (ft_isquote_escape(from + j))
			i--;
		to[i] = from[j];
		i++;
		j++;
	}
	to[i] = '\0';
}

void	escape_quotes(char **p_str)
{
	size_t	len;
	size_t	n_escape;
	char	*new;

	if (!(*p_str))
		return ;
	len = ft_strlen(*p_str);
	n_escape = count_escapes(*p_str);
	new = (char *)malloc(sizeof(char) * (len - n_escape + 1));
	if (!new)
	{
		free(*p_str);
		*p_str = NULL;
		return ;
	}
	strcpy_without_escape(*p_str, new, len - n_escape);
	free(*p_str);
	*p_str = new;
}
