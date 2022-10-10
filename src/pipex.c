/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:33:13 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:33:17 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "before_fork.h"
#include "after_fork.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	t_procinfo	*procinfo;
	pid_t		last_pid;
	int			stat_loc;

	procinfo = construct_procinfo(argc, argv, envp);
	if (!procinfo)
		return (1);
	last_pid = fork_ntimes(procinfo, procinfo->n_proc);
	procinfo_del(procinfo);
	if (last_pid > 0)
	{
		if (waitpid(last_pid, &stat_loc, 0) < 0)
		{
			perror(NULL);
			return (1);
		}
		if (procinfo->limiter)
			unlink(HEREDOC_FILENAME);
		return (WEXITSTATUS(stat_loc));
	}
	return (1);
}
