/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/10 13:54:12 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
