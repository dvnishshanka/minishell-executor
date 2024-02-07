#include "../executor.h"

/* Print the command */
void    print_cmd(t_simple_cmds *cmd)
{
    int i;

    i = 0;
    while (cmd->str[i])
    {
        printf("%d %s\n", i, cmd->str[i]);
        i ++;
    }
}

static void    free_cmd(t_simple_cmds  **cmd)
{
    free(*cmd);
}

static void    free_minishell(t_minishell  **shell)
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

void    free_all(t_minishell  **shell, t_simple_cmds  **cmd)
{
    free_cmd(cmd);
    free_minishell(shell);
}

int print_err(char  *msg)
{
    printf("%s\n", msg);
    return (1);
}