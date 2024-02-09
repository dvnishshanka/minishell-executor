#include "../executor.h"

int	handle_pipes(t_minishell *minishell, t_simple_cmds *cmd)
{
	int				fd[minishell->pipe_count][2];
	pid_t			pid[minishell->pipe_count + 1];
	int				i;
	t_simple_cmds	*head;

	i = -1;
	head = cmd;
	while (++i < minishell->pipe_count)
	{
		if (pipe(fd[i]) == -1)
			return (print_err("Error occurred in PIPES."));
	}
	i = -1;
	while (++i < (minishell->pipe_count + 1) && cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (print_err("Error occurred in forking."));
		else if (pid[i] == 0)
		{
			if (i == 0)
				dup2(fd[i][1], STDOUT_FILENO);
			else if (i == (minishell->pipe_count))
				dup2(fd[i - 1][0], STDIN_FILENO);
			else
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				dup2(fd[i][1], STDOUT_FILENO);
			}
			close_fds(fd, minishell->pipe_count);
			return (execute_commands(minishell, cmd));
		}
		cmd = cmd->next;
		if (head == cmd)
			break ;
	}
	close_fds(fd, minishell->pipe_count);
	wait_c_processes(pid, minishell->pipe_count);
	return (0);
}
