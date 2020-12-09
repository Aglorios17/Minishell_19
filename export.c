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
    while (envp[a])
        a++;
    if (!(tmp = malloc(sizeof(char *) * (a + 2))))
        return (-1);
    a = 0;
    while (envp[a])
    {
        tmp[a] = envp[a];
        a++;
    }
    tmp[a] = ft_strdup(st->tokens->content);
    tmp[a + 1] = NULL;
    st->tokens = st->firsttok;
    return (0);
}