#include "../executor.h"

// Close all file descriptors used in pipes
void    close_fds(int (*fd)[2], int pipe_count)
{
    int i;

    i = -1;
    while (++i < pipe_count)
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }
}

// Wait for all child processes
void  wait_c_processes(pid_t *pid, int pipe_count)
{
    int i;

    i = -1;
    while (++i < pipe_count + 1)
        waitpid(pid[i], NULL, 0);
}