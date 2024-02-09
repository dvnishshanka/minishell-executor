#include "../builtin.h"

/*
    echo Hello       there
    Hello there

    echo -nnnnnnnnnn "asc"
    asc

    echo -nnn -nn -nnn asc
    asc

    echo -nnn -nvn -nnn asc
    -nvn -nnn asc

If -n option is given n_option is set to 1.
*/
int	echo(t_minishell *minishell, t_simple_cmds *cmd)
{
	int	i;
	int	j;
	int	n_option;

	i = 1;
	n_option = 0;
	(void) minishell;
	while (cmd->str[i] && cmd->str[i][0] == '-' && cmd->str[i][1] == 'n')
	{
		j = 2;
		while (cmd->str[i][j] == 'n')
			j ++;
		if (cmd->str[i][j] == '\0')
		{
			n_option = 1;
			i ++;
		}
		else
			break ;
	}
	while (cmd->str[i])
	{
		printf("%s", cmd->str[i]);
		i ++;
		if (cmd->str[i])
			printf(" ");
	}
	if (!n_option)
		printf("\n");
	return (0);
}
