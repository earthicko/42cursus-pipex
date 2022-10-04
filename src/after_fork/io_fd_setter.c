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

#include "after_fork.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "libft.h"

static void	close_pipe_from_to(t_procinfo *p, int from, int to)
{
	while (from < to)
	{
		close(p->fd_pipes[from][IN]);
		close(p->fd_pipes[from][OUT]);
		from++;
	}
}

static int	set_stdin_stdout_first_proc(t_procinfo *p)
{
	int	fd_in;

	ft_printf("%d: infile %s\n", getpid(), p->infile);
	fd_in = open(p->infile, O_RDONLY);
	if (fd_in < 0)
	{
		perror(NULL);
		return (1);
	}
	ft_printf("%d: got infile fd %d\n", getpid(), fd_in);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		return (1);
	if (dup2(p->fd_pipes[0][OUT], STDOUT_FILENO) < 0)
		return (1);
	close(fd_in);
	close_pipe_from_to(p, 0, p->n_proc - 1);
	return (0);
}

static int	set_stdin_stdout_last_proc(t_procinfo *p)
{
	int	fd_out;

	ft_printf("%d: outfile %s\n", getpid(), p->outfile);
	fd_out = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out < 0)
	{
		perror(NULL);
		return (1);
	}
	ft_printf("%d: got outfile fd %d\n", getpid(), fd_out);
	if (dup2(p->fd_pipes[p->n_proc - 2][IN], STDIN_FILENO) < 0)
		return (1);
	// if (dup2(fd_out, STDOUT_FILENO) < 0)
	// 	return (1);
	// close(fd_out);
	close_pipe_from_to(p, 0, p->n_proc - 1);
	return (0);
}

static int	set_stdin_stdout_middle_proc(t_procinfo *p, int n)
{
	close_pipe_from_to(p, 0, n - 1);
	close_pipe_from_to(p, n + 1, p->n_proc - 1);
	close(p->fd_pipes[n - 1][OUT]);
	close(p->fd_pipes[n][IN]);
	if (dup2(p->fd_pipes[n - 1][IN], STDIN_FILENO) < 0)
		return (1);
	if (dup2(p->fd_pipes[n][OUT], STDOUT_FILENO) < 0)
		return (1);
	close(p->fd_pipes[n - 1][IN]);
	close(p->fd_pipes[n][OUT]);
	return (0);
}

int	set_stdin_stdout(t_procinfo *p, int n)
{
	if (n == 0 && set_stdin_stdout_first_proc(p))
		return (1);
	else if (n == p->n_proc - 1 && set_stdin_stdout_last_proc(p))
		return (1);
	else if (0 < n && n < p->n_proc - 1 && set_stdin_stdout_middle_proc(p, n))
		return (1);
	return (0);
}
