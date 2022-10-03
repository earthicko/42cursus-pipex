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

int	fork_ntimes(t_execinfo *e, int n)
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
	{
		n--;
		if (set_stdin_stdout(e, n))
			return (-1);
		return (execve(e->bins[n], e->args[n], e->envp));
	}
	else
		return (fork_ntimes(e, n - 1));
}
