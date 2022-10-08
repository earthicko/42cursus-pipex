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

#include "after_fork.h"
#include "error_msg.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "libft.h"

void	execute_child(t_procinfo *p, int i_proc)
{
	t_execinfo	*e;

	e = execinfo_init();
	if (!e)
		exit(1);
	set_stdin_stdout(p, i_proc);
	parse_args(e, p, i_proc);
	execve(e->bin, e->args, p->envp);
	execinfo_del(e);
	perror_and_exit(SHELL_NAME, 1);
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

pid_t	fork_ntimes(t_procinfo *p, int n)
{
	pid_t	pid;

	while (n)
	{
		pid = fork();
		if (pid == -1)
		{
			perror(NULL);
			return (-1);
		}
		if (pid == 0)
			execute_child(p, p->n_proc - n);
		n--;
	}
	return (pid);
}
