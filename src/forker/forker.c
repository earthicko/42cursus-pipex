#include "datatypes.h"
#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

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
        ft_printf("%5d: binary: %s\n", getpid(), e->bins[n]);
        return (0);
    } else {
        ft_printf("%5d: I forked new process at pid %d\n", getpid(), pid);
        wait(NULL);
        return fork_ntimes(e, n - 1);
    }
}
