#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

const int n_process = 5;

int fork_ntimes(int (*pipes)[2], int n)
{
    pid_t	pid;

    if (n <= 0) return 0;

    pid = fork();

    if (pid == -1)
	{
		perror(NULL);
        return -1;
    }
    if (pid == 0) {
        printf("%5d: I am forked new process\n", getpid());
        printf("%5d: n for me is %d\n", getpid(), n);
        printf("%5d: pipe is %d -> %d\n", getpid(), pipes[n - 1][0],
               pipes[n - 1][1]);
        return 0;
    } else {
        printf("%5d: I forked new process at pid %d\n", getpid(), pid);
        wait(NULL);
        return fork_ntimes(pipes, n - 1);
    }
}
