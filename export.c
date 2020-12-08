#include "minishell.h"

int ft_dollars(shell *st)
{
    (void)st;
    return (0);
}

int ft_export(shell *st, char **envp)
{
    char **tmp;
    int a;

    tmp = NULL;
    a = 0;
    if (!st->tokens->next)
        return (-1);
    st->tokens = st->tokens->next;
    tmp = envp;
    while (tmp[a])
        a++;
    tmp[a] = ft_strdup(st->tokens->content);
    tmp[a + 1] = '\0';
    envp = tmp;
    st->tokens = st->firsttok;
    return (0);
}