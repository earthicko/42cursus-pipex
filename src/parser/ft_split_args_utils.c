/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/10 13:54:12 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static void	skip_until_quote(char **str, char quote)
{
	(*str)++;
	while (**str != '\0' && !(**str == quote && *(*str - 1) != '\\'))
		(*str)++;
	if (**str == quote)
		(*str)++;
	if (!ft_isspace(**str))
		skip_space(str, 1);
}

void	skip_space(char **str, int inverted)
{
	if (inverted)
	{
		while (**str != '\0' && !ft_isspace(**str))
		{
			if (ft_isquote(**str))
			{
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
