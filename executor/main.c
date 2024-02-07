#include "../executor.h"
#include "../builtin.h"

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    t_minishell *shell_1;
    t_simple_cmds   *simple_cmd_11;

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
    simple_cmd_11->str[0] =  "ls";
    simple_cmd_11->str[1] = "-al";
    simple_cmd_11->str[2] = NULL;
    simple_cmd_11->str[3] = NULL;
    simple_cmd_11->builtin = NULL;

    // CAT
    // simple_cmd_11->str[0] =  "cat";
    // simple_cmd_11->str[1] = "test.txt";
    // simple_cmd_11->str[2] = NULL;
    // simple_cmd_11->str[3] = NULL;
    // simple_cmd_11->builtin = NULL;

    simple_cmd_11->num_redirections = 0;
    simple_cmd_11->hd_file_name = NULL;
    // simple_cmd_11->redirections = NULL;
    simple_cmd_11->next = NULL;
    simple_cmd_11->prev = NULL;

    print_cmd(simple_cmd_11);
    execute(shell_1, simple_cmd_11);
    free_all(&shell_1, &simple_cmd_11);
    return (0);
}
