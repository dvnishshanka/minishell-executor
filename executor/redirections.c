#include "../executor.h"

static int	redirect(int *fd, t_lexer *tmp)
{
	if (tmp->token == 1)
	{
		*fd = open(tmp->str, O_RDONLY);
		if (*fd == -1)
			return (print_err(tmp->str));
		dup2(*fd, STDIN_FILENO);
	}
	else if (tmp->token == -1)
	{
		*fd = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (*fd == -1)
			return (print_err(tmp->str));
		if (dup2(*fd, STDOUT_FILENO) == -1)
			return (print_err("Dup2"));
	}
	else if (tmp->token == -2)
	{
		*fd = open(tmp->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*fd == -1)
			return (print_err(tmp->str));
		if (dup2(*fd, STDOUT_FILENO) == -1)
			return (print_err("Dup2"));
	}
	return (0);
}

/*
token	1	<
token	-1	>
token	-2	>>

O_WRONLY	Open the file for writing only.
				This means that data can be written to the file,
				but reading from it is not allowed.
O_CREAT		Create the file if it doesn't exist.
				If the file exists, this flag has no effect.
O_TRUNC		If the file exists and is writable,
				its length is truncated to 0 bytes.
				If the file does not exist, it is created.
				When a file is truncated, all of its contents are removed,
				effectively making it an empty file.
O_APPEND		Sets the file offset to the end of the file prior to each write.
file permissions are represented using a 3-digit octal number.
Each digit in the octal number represents permissions for different
	groups: owner, group, and others.
Owner:   6  4  4
         r  w  r
Group:   r  -  -
Others:  r  -  -

dup 2
file descriptor newfd is adjusted so that it now refers
	to the same open file description as oldfd.
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
		if (redirect(&fd, tmp))
			return (redirect(&fd, tmp));
		tmp = tmp->next;
		if (head == tmp)
			break ;
	}
	return (0);
}
