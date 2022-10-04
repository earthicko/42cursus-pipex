/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:34:07 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:34:08 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	execute_child(t_execinfo *e, int i_proc)
{
	if (set_stdin_stdout(e, i_proc))
		return (-1);
	return (execve(e->bins[i_proc], e->args[i_proc], e->envp));
}

int	wait_for_last_child(pid_t pid)
{
	int		stat_loc;

	if (waitpid(pid, &stat_loc, 0) < 0)
	{
		perror(NULL);
		return (-1);
	}
	return (WEXITSTATUS(stat_loc));
}

int	fork_ntimes(t_execinfo *e, int n)
{
	pid_t	pid;
	int		i_proc;

	if (n <= 0)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	if (pid == 0)
		return (execute_child(e, e->n_proc - n));
	else
	{
		if (n == 1)
			return (wait_for_last_child(pid));
		return (fork_ntimes(e, n - 1));
	}
}
