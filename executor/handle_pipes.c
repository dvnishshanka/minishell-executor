#include "../executor.h"

static void	free_fd(int	***fd, int arr_no)
{
	int	i;

	i = -1;
	while (++i < arr_no)
	{
		free((*fd)[i]);
	}
	free(*fd);
}

static int	create_pipes(t_minishell *minishell, int ***fd, pid_t **pid)
{
	int	i;

	i = -1;
	while (++i < minishell->pipe_count)
	{
		(*fd)[i] = (int *)calloc(2, sizeof(int));
		if ((*fd)[i] == NULL)
		{
			free(*pid);
			free_fd(fd, i);
			return (print_err("Error occurred in Calloc."));
		}
		if (pipe((*fd)[i]) == -1)
		{
			free(*pid);
			free_fd(fd, i + 1);
			return (print_err("Error occurred in PIPES."));
		}
	}
	return (0);
}


int	handle_pipes(t_minishell *minishell, t_simple_cmds *cmd)
{
	int				**fd;
	pid_t			*pid;
	int				i;
	t_simple_cmds	*head;

	fd = (int **)calloc(minishell->pipe_count, sizeof(int *));
	if (fd == NULL)
		return (print_err("Error occurred in Calloc."));
	pid = (pid_t *)calloc(minishell->pipe_count + 1, sizeof(pid_t));
	if (!pid)
	{
		free(fd);
		return (print_err("Error occurred in Calloc."));
	}
	i = -1;
	head = cmd;
	if (create_pipes(minishell, &fd, &pid))
		return (1);
	while (++i < (minishell->pipe_count + 1) && cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			free_fd(&fd, minishell->pipe_count);
			free(pid);
			return (print_err("Error occurred in forking."));
		}
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
			free_fd(&fd, minishell->pipe_count);
			free(pid);
			return (execute_commands(minishell, cmd));
		}
		cmd = cmd->next;
		if (head == cmd)
			break ;
	}
	close_fds(fd, minishell->pipe_count);
	wait_c_processes(pid, minishell->pipe_count);
	free_fd(&fd, minishell->pipe_count);
	free(pid);
	return (0);
}
