#include "../executor.h"

/* Print the command */
void	print_cmd(t_simple_cmds *cmd)
{
	int i;

	i = 0;
	while (cmd->str[i])
	{
		printf("%d %s\n", i, cmd->str[i]);
		i ++;
	}
}

static void	free_cmd(t_simple_cmds  **cmd)
{
	t_lexer	*tmp;
	t_lexer	*head;

	head = (*cmd)->redirections;
	tmp = head;
	while (tmp)
	{
		tmp = (*cmd)->redirections->next;
		free((*cmd)->redirections);
		(*cmd)->redirections = tmp;
		if (tmp == head)
			break;
	}
	free(*cmd);

}

static void	free_minishell(t_minishell  **shell)
{
	int i;

	i = 0;
	while ((*shell)->paths[i])
	{
		free((*shell)->paths[i]);
		i ++;
	}
	if ((*shell)->paths)
		free((*shell)->paths);
	free(*shell);
}

void	free_all(t_minishell  **shell, t_simple_cmds  **cmd)
{
	t_simple_cmds	*tmp;
	t_simple_cmds	*head;

	if (!cmd || !(*cmd))
		return ;
	tmp = (*cmd);
	head = (*cmd);
	while (*cmd)
	{
		tmp = (*cmd)->next;
		free_cmd(cmd);
		*cmd = tmp;
		if (*cmd == head)
			break;
	}
	free_minishell(shell);
}

int	print_err(char  *msg)
{
	perror(msg);
	return (1);
}
