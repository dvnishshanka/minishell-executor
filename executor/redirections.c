#include "../executor.h"

/*
token	1	<
token	-1	>

dup 2
file descriptor newfd is adjusted so that it now refers to the same open file description as oldfd.
*/
int	handle_redirections(t_simple_cmds *cmd)
{
	t_lexer	*head;
	t_lexer	*tmp;
	int		fd;
	
	head = cmd->redirections;
	tmp = head;
	while (tmp)
	{
		if (tmp->token == 1)
		{
			fd = open(tmp->str, O_RDONLY);
			if (fd == -1)
				return (print_err("Open"));
			dup2(fd, STDIN_FILENO);
		}
		else if (tmp->token == -1)
		{
			fd = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC);
			if (fd == -1)
				return (print_err("Write"));
			printf("fd %d %d\n",fd, STDOUT_FILENO);	

			if (dup2(fd, STDOUT_FILENO) == -1)
			{	
				
printf("fd %d\n",fd);
				return (print_err("Dup2"));}
		}
		tmp = tmp->next;
		if (head == tmp)
			break;
	}
	return (0);
}
