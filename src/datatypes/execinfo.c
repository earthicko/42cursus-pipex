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
#include <unistd.h>
#include <stdio.h>

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
	int	i;

	if (execinfo->fd_pipes)
	{
		i = 0;
		while (i < execinfo->n_proc - 1)
		{
			close(execinfo->fd_pipes[i][0]);
			close(execinfo->fd_pipes[i][1]);
			i++;
		}
		intarr2_del(execinfo->fd_pipes);
	}
	if (execinfo->fd_in && close(execinfo->fd_in))
		perror(NULL);
	if (execinfo->fd_out && close(execinfo->fd_out))
		perror(NULL);
	if (execinfo->bins)
		strarr2_del(execinfo->bins);
	free(execinfo);
	return (NULL);
}
