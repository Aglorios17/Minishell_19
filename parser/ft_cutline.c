#include "../include/minishell.h"

int	ft_cutline(shell *st)
{
	int a;
	char **line;
	a = 0;
	line = ft_splitms(st->line, ';', st);
	while (line[a])
	{
		ft_lstadd_back(&st->cutline, ft_lstnew(ft_strdup(line[a])));
		a++;
	}
//	printf("envv1|%s|\n", (char *)st->envv->content);
	st->firstcut = st->cutline;
/*
	while (st->cutline != NULL)
	{
		printf("cut|%s|\n", (char *)st->cutline->content);
		st->cutline = st->cutline->next;
	}
	st->cutline = st->firstcut;
*/
    return (0);
}
