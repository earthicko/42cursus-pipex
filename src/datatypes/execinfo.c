/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execinfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:30 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:31 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "datatypes.h"

t_execinfo	*execinfo_init(void)
{
	t_execinfo	*init;

	init = (t_execinfo *)malloc(sizeof(t_execinfo));
	if (!init)
		return (NULL);
	ft_memset(init, 0, sizeof(t_execinfo));
	return (init);
}

t_execinfo	*execinfo_del(t_execinfo *execinfo)
{
	if (execinfo->bin)
		free(execinfo->bin);
	if (execinfo->args)
		strarr2_del(execinfo->args);
	free(execinfo);
	return (NULL);
}
