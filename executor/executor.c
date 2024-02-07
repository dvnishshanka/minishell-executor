#include "../executor.h"

/*
pid = 0 in the Child Process.

For each directory, we construct the full path of the command and check if it's executable using the "access" function.
If the command is found and executable, we execute it using "execve".
On success, execve() does not return, on error -1 is returned. That's why we need to call it inside the child process.
    int execve(const char *pathname, char *const _Nullable argv[], char *const _Nullable envp[])
X_OK Flag meaning test for execute/search permission.

The input command can be in the form of 'ls' or '/bin/ls'
In the 'ls' form we search through executables by constructing possible full paths.
*/
static int execute_cmd(t_minishell *minishell, t_simple_cmds   *cmd)
{
    pid_t   pid;
    int i;
    char    *pathname;

    i = 0;
    pid = fork();
    if (pid == -1)
        return (print_err("Error occurred in forking."));
    else if (pid == 0)
    {
        while (minishell->paths[i])
        {
            pathname = ft_strjoin(minishell->paths[i], cmd->str[0]);
            if (access(pathname, X_OK) == 0)
            {    
                if (execve(pathname, cmd->str, minishell->paths) == -1)
                    return (print_err("Error occurred in execve."));
            }
            i++;
        }
        if (execve(cmd->str[0], cmd->str, minishell->paths) == -1)
              return (print_err("Error occurred in execve."));
    }
    else
        wait(NULL);
    return (0);
}

/*
*/
int execute(t_minishell *minishell, t_simple_cmds   *cmd)
{
    if (cmd->builtin != NULL)
        cmd->builtin(minishell, cmd);
    else
        execute_cmd(minishell, cmd);
    return (0);
}