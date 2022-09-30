#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

const int n_process = 5;

int fork_ntimes(int (*pipes)[2], int n) {
    __pid_t pid;

    if (n <= 0) return 0;
    pid = fork();
    if (pid == -1) {
        printf("Failed to fork\n");
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

int main() {
    printf("%5d: Root\n", getpid());

    int pipes[n_process][2];

    for (int i = 0; i < n_process; i++) pipe(pipes[i]);
    for (int i = 0; i < n_process; i++)
        printf("pipe created [%d][%d]\n", pipes[i][0], pipes[i][1]);
    fork_ntimes(pipes, n_process);

    return 0;
}