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

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_isquote_literal(char *p_c)
{
	if (ft_isquote(*p_c) && *(p_c - 1) != '\\')
		return (1);
	return (0);
}

int	ft_isquote_escape(char *p_c)
{
	if (ft_isquote(*p_c) && *(p_c - 1) == '\\')
		return (1);
	return (0);
}

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
		// strip_quotes(p_str);
	}
}

void	escape_quotes(char **p_str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	n_escape;
	char	*new;

	if (!(*p_str))
		return ;
	len = ft_strlen(*p_str);
	n_escape = 0;
	i = 1;
	while (i < len)
	{
		if (ft_isquote_escape((*p_str) + i))
			n_escape++;
		i++;
	}
	new = (char *)malloc(sizeof(char) * (len - n_escape + 1));
	if (!new)
	{
		free(*p_str);
		*p_str = NULL;
		return ;
	}
	i = 0;
	j = 0;
	while (i < len - n_escape)
	{
		if (ft_isquote_escape((*p_str) + j))
			i--;
		new[i] = (*p_str)[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(*p_str);
	*p_str = new;
}
