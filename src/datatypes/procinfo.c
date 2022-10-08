/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procinfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:30 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:31 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "datatypes.h"
#include <unistd.h>
#include <stdio.h>

t_procinfo	*procinfo_init(void)
{
	t_procinfo	*init;

	init = (t_procinfo *)malloc(sizeof(t_procinfo));
	if (!init)
		return (NULL);
	ft_memset(init, 0, sizeof(t_procinfo));
	return (init);
}

t_procinfo	*procinfo_del(t_procinfo *procinfo)
{
	int	i;

	if (procinfo->fd_pipes)
	{
		i = 0;
		while (i < procinfo->n_proc - 1)
		{
			close(procinfo->fd_pipes[i][0]);
			close(procinfo->fd_pipes[i][1]);
			i++;
		}
		intarr2_del(procinfo->fd_pipes);
	}
	if (procinfo->limiter)
		free(procinfo->limiter);
	if (procinfo->coms)
		strarr2_del(procinfo->coms);
	if (procinfo->paths)
		strarr2_del(procinfo->paths);
	free(procinfo);
	return (NULL);
}
