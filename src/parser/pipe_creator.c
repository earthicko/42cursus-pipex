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

int	open_in_out_files(t_execinfo *execinfo, int argc, char **argv)
{
	execinfo->fd_in = open(argv[1], O_RDONLY);
	if (execinfo->fd_in < 0)
	{
		perror(NULL);
		return (-1);
	}
	execinfo->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (execinfo->fd_out < 0)
	{
		perror(NULL);
		if (close(execinfo->fd_in))
			perror(NULL);
		return (-1);
	}
	return (0);
}

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

int	create_pipes(t_execinfo *execinfo)
{
	int	n_pipes;

	n_pipes = execinfo->n_proc - 1;
	execinfo->fd_pipes = intarr2_init(n_pipes, 2);
	if (!execinfo->fd_pipes)
		return (-1);
	if (deploy_pipes(execinfo->fd_pipes, n_pipes))
	{
		intarr2_del(execinfo->fd_pipes);
		return (-1);
	}
	return (0);
}
