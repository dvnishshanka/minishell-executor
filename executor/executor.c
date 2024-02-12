#include "../executor.h"

/*
pid = 0 in the Child Process.

For each directory, we construct the full path of the command
and check if it's executable using the "access" function.
If the command is found and executable, we execute it using "execve".
On success, execve() does not return, on error -1 is returned.
That's why we need to call it inside the child process.

int execve(const char *pathname,
	char *const _Nullable argv[], char *const _Nullable envp[])

X_OK Flag meaning test for execute/search permission.

The input command can be in the form of 'ls' or '/bin/ls'
In the 'ls' form we search through executables by
constructing possible full paths.
*/
static int	execute_executables(t_minishell *minishell, t_simple_cmds *cmd)
{
	pid_t	pid;
	int		i;
	char	*pathname;

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
				{
					free(pathname);
					return (print_err("Error occurred in execve."));
				}
			}
			i++;
			free(pathname);
		}
		if (execve(cmd->str[0], cmd->str, minishell->paths) == -1)
			return (print_err("Error occurred in execve."));
	}
	else
		wait(NULL);
	return (0);
}

/* Checks whether command is a builtin one or not*/
int	execute_commands(t_minishell *minishell, t_simple_cmds *cmd)
{
	if (cmd->builtin != NULL)
		return (cmd->builtin(minishell, cmd));
	else
		return (execute_executables(minishell, cmd));
}

/*
PIPE
    fd[0] for the read end of pipe
    fd[1] for the write end of pipe

dup2
    int dup2(int oldfd, int newfd);
    The file descriptor newfd is adjusted so that
	it now refers to the same open file description as oldfd.
*/
int	execute(t_minishell *minishell, t_simple_cmds *cmd)
{
	if (minishell->pipe_count > 0)
		return (handle_pipes(minishell, cmd));
	return (execute_commands(minishell, cmd));
}
