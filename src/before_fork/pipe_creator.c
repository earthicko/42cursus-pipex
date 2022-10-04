/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:55 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:56 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static void	revert_deploy_pipes(int **pipes, int from)
{
	int	i;

	i = 0;
	while (i < from)
	{
		if (close(pipes[i][0]))
			perror(NULL);
		if (close(pipes[i][1]))
			perror(NULL);
		i++;
	}
}

static int	deploy_pipes(int **pipes, int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		if (pipe(pipes[i]))
		{
			perror(NULL);
			revert_deploy_pipes(pipes, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	create_pipes(t_procinfo *procinfo)
{
	int	n_pipes;

	n_pipes = procinfo->n_proc - 1;
	procinfo->fd_pipes = intarr2_init(n_pipes, 2);
	if (!procinfo->fd_pipes)
		return (-1);
	if (deploy_pipes(procinfo->fd_pipes, n_pipes))
	{
		intarr2_del(procinfo->fd_pipes);
		return (-1);
	}
	return (0);
}
