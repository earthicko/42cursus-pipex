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
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "libft.h"

int	execute_child(t_procinfo *p, int i_proc)
{
	t_execinfo	*e;
	int			status;

	e = execinfo_init();
	if (!e)
		return (-1);
	status = parse_args(e, p, i_proc);
	if (status)
	{
		execinfo_del(e);
		return (status);
	}

	ft_printf("%d: command: %s\n", getpid(), p->coms[i_proc]);
	ft_printf("%d: bin: %s\n", getpid(), e->bin);
	ft_printf("%d: args:\n", getpid());
	char **str = e->args;
	while (*str){ft_printf("\t%s\n", *str);str++;}

	status = set_stdin_stdout(p, i_proc);
	if (status)
	{
		execinfo_del(e);
		return (status);
	}
	ft_printf("%d: ready to exec\n", getpid());
	execve(e->bin, e->args, p->envp);
	return (0);
}

int	wait_for_last_child(pid_t pid)
{
	int		stat_loc;

	ft_printf("waiting for last child...\n");
	if (waitpid(pid, &stat_loc, 0) < 0)
	{
		perror(NULL);
		return (-1);
	}
	return (WEXITSTATUS(stat_loc));
}

int	fork_ntimes(t_procinfo *p, int n)
{
	pid_t	pid;

	if (n <= 0)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	if (pid == 0)
		return (execute_child(p, p->n_proc - n));
	else
	{
		ft_printf("%d: n=%d, forked child\n", getpid(), n);
		if (n == 1)
			return (wait_for_last_child(pid));
		return (fork_ntimes(p, n - 1));
	}
}
