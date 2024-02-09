#include "../executor.h"

/* Add executable directory paths*/
int    add_paths(t_minishell **shell_1)
{
    int     i;
    char    *tmp;

    i = 0;
    if (!shell_1 || !(*shell_1))
    {
        printf("Error occurred.\n");
        return (1);
    }
    (*shell_1)->paths = ft_split(getenv("PATH"), ':');
    if (!((*shell_1)->paths))
    {
        printf("Error in spliting the 'PATH'.\n");
        return (1);
    }
    while ((*shell_1)->paths[i])
    {
        tmp = ft_strjoin((*shell_1)->paths[i], "/");
        free((*shell_1)->paths[i]);
        (*shell_1)->paths[i] = ft_strdup(tmp);
        free(tmp);
        i ++;
    }
    return (0);
}