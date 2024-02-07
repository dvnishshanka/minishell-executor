#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

#include "libraries/libft/libft.h"

struct  s_minishell;

typedef struct s_simple_cmds
{
	char                    *str[4];
	int                     (*builtin)(struct s_minishell *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	// t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}   t_simple_cmds;

/*
paths are where the executables are located.
	eg: /usr/local/sbin/
*/
typedef struct s_minishell
{
	// t_dict	*dict;
	// t_lexer	*lex;
	t_simple_cmds	*cmd;
	// char	*pwd;
	// char	*old_pwd;
	char	**paths;
}   t_minishell;

// executor.c
int execute(t_minishell *minishell, t_simple_cmds   *cmd);

// other_utils.c
void    print_cmd(t_simple_cmds *cmd);
void    free_all(t_minishell  **shell, t_simple_cmds  **cmd);
int print_err(char  *msg);

// env_utils.c
int    add_paths(t_minishell **shell_1);
#endif