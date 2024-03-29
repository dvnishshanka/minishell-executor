#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libraries/libft/libft.h"

struct	s_minishell;

typedef struct s_lexer
{
	char			*str;
	int				token;
	// int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

/*
In redirections, int token helps to identify the token.
*/
typedef struct s_simple_cmds
{
	char					*str[4];
	char					*hd_file_name;
	int						(*builtin)(struct s_minishell *,
			struct s_simple_cmds *);
	int						num_redirections;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

/*
paths are where the executables are located.
	eg: /usr/local/sbin/
pipe_count is the no of pipes.
*/
typedef struct s_minishell
{
	// t_dict	*dict;
	// t_lexer	*lex;
	t_simple_cmds	*cmd;
	// char	*pwd;
	// char	*old_pwd;
	char			**paths;
	int				pipe_count;
}	t_minishell;

// executor.c
int		execute(t_minishell *minishell, t_simple_cmds *cmd);
int		execute_commands(t_minishell *minishell, t_simple_cmds *cmd);

// handle_pipes.c
int		handle_pipes(t_minishell *minishell, t_simple_cmds *cmd);

// redirections.c
int		handle_redirections(t_simple_cmds *cmd);

// pipe_utils.c
void	close_fds(int **fd, int pipe_count);
void	wait_c_processes(pid_t *pid, int pipe_count);

// other_utils.c
void	print_cmd(t_simple_cmds *cmd);
void	free_all(t_minishell **shell, t_simple_cmds **cmd);
int		print_err(char *msg);

// env_utils.c
int		add_paths(t_minishell **shell_1);
#endif
