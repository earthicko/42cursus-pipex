/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_fd_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:34:08 by donghyle          #+#    #+#             */
/*   Updated: 2022/10/03 17:34:11 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <unistd.h>

static void	close_pipe_from_to(t_execinfo *e, int from, int to)
{
	while (from < to)
	{
		close(e->fd_pipes[from][IN]);
		close(e->fd_pipes[from][OUT]);
		from++;
	}
}

static int	set_stdin_stdout_first_proc(t_execinfo *e)
{
	close_pipe_from_to(e, 1, e->n_proc - 1);
	close(e->fd_pipes[0][IN]);
	if (dup2(e->fd_in, STDIN_FILENO) < 0)
		return (-1);
	if (dup2(e->fd_pipes[0][OUT], STDOUT_FILENO) < 0)
		return (-1);
	close(e->fd_in);
	close(e->fd_pipes[0][OUT]);
	return (0);
}

static int	set_stdin_stdout_last_proc(t_execinfo *e)
{
	close_pipe_from_to(e, 0, e->n_proc - 2);
	close(e->fd_pipes[e->n_proc - 2][OUT]);
	if (dup2(e->fd_pipes[e->n_proc - 2][IN], STDIN_FILENO) < 0)
		return (-1);
	if (dup2(e->fd_out, STDOUT_FILENO) < 0)
		return (-1);
	close(e->fd_pipes[e->n_proc - 2][IN]);
	close(e->fd_out);
	return (0);
}

static int	set_stdin_stdout_middle_proc(t_execinfo *e, int n)
{
	close_pipe_from_to(e, 0, n - 1);
	close_pipe_from_to(e, n + 1, e->n_proc - 1);
	close(e->fd_pipes[n - 1][OUT]);
	close(e->fd_pipes[n][IN]);
	if (dup2(e->fd_pipes[n - 1][IN], STDIN_FILENO) < 0)
		return (-1);
	if (dup2(e->fd_pipes[n][OUT], STDOUT_FILENO) < 0)
		return (-1);
	close(e->fd_pipes[n - 1][IN]);
	close(e->fd_pipes[n][OUT]);
	return (0);
}

int	set_stdin_stdout(t_execinfo *e, int n)
{
	if (n == 0 && set_stdin_stdout_first_proc(e))
		return (-1);
	else if (n == e->n_proc - 1 && set_stdin_stdout_last_proc(e))
		return (-1);
	else if (0 < n && n < e->n_proc - 1 && set_stdin_stdout_middle_proc(e, n))
		return (-1);
	return (0);
}
