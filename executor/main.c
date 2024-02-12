#include "../executor.h"
#include "../builtin.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_minishell		*shell_1;
	t_simple_cmds	*simple_cmd_11;

	shell_1 = (t_minishell *)ft_calloc(2, sizeof(t_minishell));
	if (!shell_1)
		return (1);
	if (add_paths(&shell_1))
	{
		free(shell_1);
		return (1);
	}
	// Print Paths
	/*
	int i = 0;
	while (shell_1->paths[i])
	{
		printf("%s\n", shell_1->paths[i]);
		i++;
	}
	*/

	simple_cmd_11 = (t_simple_cmds *)ft_calloc(2, sizeof(t_simple_cmds));
	if (!simple_cmd_11)
	{
		free(shell_1);
		return (1);
	}

	shell_1->cmd = simple_cmd_11;
	// shell_1->pipe_count = 0;

	// ECHO
	// simple_cmd_11->str[0] =  "echo";
	// simple_cmd_11->str[1] = "-nvn";
	// simple_cmd_11->str[2] = "-he";
	// simple_cmd_11->str[3] = NULL;
	// simple_cmd_11->builtin = echo;

	// /bin/ls -al
	// simple_cmd_11->str[0] =  "/bin/ls";
	// simple_cmd_11->str[1] = "-al";
	// simple_cmd_11->str[2] = NULL;
	// simple_cmd_11->str[3] = NULL;
	// simple_cmd_11->builtin = NULL;

	// ls -al
	// simple_cmd_11->str[0] =  "ls";
	// simple_cmd_11->str[1] = "-al";
	// simple_cmd_11->str[2] = NULL;
	// simple_cmd_11->str[3] = NULL;
	// simple_cmd_11->builtin = NULL;

	// CAT
	// simple_cmd_11->str[0] =  "cat";
	// simple_cmd_11->str[1] = "test.txt";
	// simple_cmd_11->str[2] = NULL;
	// simple_cmd_11->str[3] = NULL;
	// simple_cmd_11->builtin = NULL;

	// simple_cmd_11->num_redirections = 0;
	// simple_cmd_11->hd_file_name = NULL;
	// simple_cmd_11->next = NULL;
	// simple_cmd_11->prev = NULL;

	// PIPE TESTING START
	t_simple_cmds   *simple_cmd_12;
	simple_cmd_12 = (t_simple_cmds *)ft_calloc(2, sizeof(t_simple_cmds));
	if (!simple_cmd_12)
	{
		free(simple_cmd_11);
		free(shell_1);
		return (1);
	}
	t_simple_cmds   *simple_cmd_13;
	simple_cmd_13 = (t_simple_cmds *)ft_calloc(2, sizeof(t_simple_cmds));
	if (!simple_cmd_13)
	{
		free(simple_cmd_11);
		free(simple_cmd_12);
		free(shell_1);
		return (1);
	}
	shell_1->pipe_count = 0;

	simple_cmd_11->str[0] =  "emacs" ;
	simple_cmd_11->str[1] = NULL ;
	simple_cmd_11->str[2] = NULL;
	simple_cmd_11->str[3] = NULL;
	simple_cmd_11->builtin = NULL;

	simple_cmd_12->str[0] =  NULL;
	simple_cmd_12->str[1] = NULL;
	simple_cmd_12->str[2] = NULL;
	simple_cmd_12->str[3] = NULL;
	simple_cmd_12->builtin = NULL;

	simple_cmd_13->str[0] =  NULL;
	simple_cmd_13->str[1] = NULL;
	simple_cmd_13->str[2] = NULL;
	simple_cmd_13->str[3] = NULL;
	simple_cmd_13->builtin = NULL;

	simple_cmd_11->num_redirections = 0;
	simple_cmd_11->hd_file_name = NULL;
	simple_cmd_11->next = simple_cmd_12;
	simple_cmd_11->prev = simple_cmd_13;

	simple_cmd_12->num_redirections = 0;
	simple_cmd_12->hd_file_name = NULL;
	simple_cmd_12->next = simple_cmd_13;
	simple_cmd_12->prev = simple_cmd_11;

	simple_cmd_13->num_redirections = 0;
	simple_cmd_13->hd_file_name = NULL;
	simple_cmd_13->next = simple_cmd_11;
	simple_cmd_13->prev = simple_cmd_12;
		// PIPE TESTING END

	// print_cmd(simple_cmd_11);
	execute(shell_1, simple_cmd_11);
	free_all(&shell_1, &simple_cmd_11);
	return (0);
}
