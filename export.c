#include "minishell.h"

int ft_export(shell *st, char **envp)
{
    char **tmp;
    int a;

    tmp = NULL;
    a = 0;
//    printf("OK\n");
    if (!st->tokens->next)
        return (-1);
    st->tokens = st->tokens->next;
//    printf("%s\n", envp[a]);
    while (envp && envp[a])
    {
        tmp[a] = ft_strdup(envp[a]);
//        printf("%s\n", envp[a]);
        a++;
        printf("%s\n", tmp[a]);
    }
    st->tokens = st->firsttok;
    return (0);
}