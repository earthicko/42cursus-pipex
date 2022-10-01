#include "datatypes.h"
#include "libft.h"
#include "forker.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static void	close_pipe_from_to(t_execinfo *e, int from, int to)
{
	while (from < to)
	{
		// ft_printf("%5d: close pipe %d\n", getpid(), from);
		close(e->fd_pipes[from][IN]);
		close(e->fd_pipes[from][OUT]);
		from++;
	}
}

static int	set_stdin_stdout(t_execinfo *e, int n)
{
	if (n == 0)
	{
		// ft_printf("%5d: first process, in %d out %d\n", getpid(), e->fd_in, e->fd_pipes[0][0]);
		close_pipe_from_to(e, 1, e->n_command - 1);
		close(e->fd_pipes[0][IN]);
		if (dup2(e->fd_in, STDIN_FILENO))
			return (-1);
		if (dup2(e->fd_pipes[0][OUT], STDOUT_FILENO))
			return (-1);
		close(e->fd_in);
		close(e->fd_pipes[0][OUT]);
	}
	else if (n == e->n_command - 1)
	{
		// ft_printf("%5d: last process, in %d out %d\n", getpid(), e->fd_pipes[e->n_command - 2][1], e->fd_out);
		close_pipe_from_to(e, 0, e->n_command - 2);
		close(e->fd_pipes[e->n_command - 2][OUT]);
		if (dup2(e->fd_pipes[e->n_command - 2][IN], STDIN_FILENO))
			return (-1);
		if (dup2(e->fd_out, STDOUT_FILENO))
			return (-1);
	}
	else
	{
		// ft_printf("%5d: %dth process, in %d out %d\n", getpid(), n, e->fd_pipes[n - 1][1], e->fd_pipes[n][0]);
		close_pipe_from_to(e, 0, n - 1);
		close_pipe_from_to(e, n + 1, e->n_command - 1);
		close(e->fd_pipes[n - 1][OUT]);
		close(e->fd_pipes[n][IN]);
		if (dup2(e->fd_pipes[n - 1][IN], STDIN_FILENO))
			return (-1);
		if (dup2(e->fd_pipes[n][OUT], STDOUT_FILENO))
			return (-1);
		close(e->fd_pipes[n - 1][IN]);
		close(e->fd_pipes[n][OUT]);
	}
	return (0);
}

int fork_ntimes(t_execinfo *e, int n)
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
    if (pid == 0) {
        ft_printf("%5d: I am forked new process\n", getpid());
		n--;
		if (set_stdin_stdout(e, n))
			return (-1);
        return (execve(e->bins[n], e->args[n], e->envp));
    } else {
        ft_printf("%5d: I forked new process at pid %d\n", getpid(), pid);
        wait(NULL);
        return fork_ntimes(e, n - 1);
    }
}
