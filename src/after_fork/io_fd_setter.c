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

#include "libft.h"
#include "after_fork.h"
#include "error_msg.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void	buffer_in_heredoc(t_procinfo *p)
{
	int		file;
	char	*buf;

	file = open(HEREDOC_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		perror_and_exit(SHELL_NAME, 1);
	while (1)
	{
		ft_printf("heredoc> ");
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
		{
			unlink(HEREDOC_FILENAME);
			exit(1);
		}
		if (heredoc_end(p->limiter, buf))
			break ;
		ft_dprintf(file, buf);
		free(buf);
	}
	free(buf);
	close(file);
}

static void	set_stdin_stdout_first_proc(t_procinfo *p)
{
	int	fd_in;

	if (p->limiter)
		buffer_in_heredoc(p);
	fd_in = open(p->infile, O_RDONLY);
	if (fd_in < 0)
		perror_nofile_and_exit(p->infile, 1);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		perror_and_exit(SHELL_NAME, 1);
	if (dup2(p->fd_pipes[0][OUT], STDOUT_FILENO) < 0)
		perror_and_exit(SHELL_NAME, 1);
	close(fd_in);
	close_all_pipes(p);
}

static void	set_stdin_stdout_last_proc(t_procinfo *p)
{
	int	fd_out;

	fd_out = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out < 0)
		perror_nofile_and_exit(p->outfile, 1);
	if (dup2(p->fd_pipes[p->n_proc - 2][IN], STDIN_FILENO) < 0)
		perror_and_exit(SHELL_NAME, 1);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		perror_and_exit(SHELL_NAME, 1);
	close(fd_out);
	close_all_pipes(p);
}

static void	set_stdin_stdout_middle_proc(t_procinfo *p, int n)
{
	if (dup2(p->fd_pipes[n - 1][IN], STDIN_FILENO) < 0)
		perror_and_exit(SHELL_NAME, 1);
	if (dup2(p->fd_pipes[n][OUT], STDOUT_FILENO) < 0)
		perror_and_exit(SHELL_NAME, 1);
	close_all_pipes(p);
}

void	set_stdin_stdout(t_procinfo *p, int n)
{
	if (n == 0)
		set_stdin_stdout_first_proc(p);
	else if (n == p->n_proc - 1)
		set_stdin_stdout_last_proc(p);
	else if (0 < n && n < p->n_proc - 1)
		set_stdin_stdout_middle_proc(p, n);
}
