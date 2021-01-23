#include "../include/minishell.h"

int	ft_cutpipe(shell *st)
{
	int a;
	char **line;
	a = 0;
	line = ft_splitms((char *)st->cutline->content, '|', st);
	while (line[a])
	{
		ft_lstadd_back(&st->pipe, ft_lstnew(ft_strdup(line[a])));
		a++;
	}
	st->firstpipe = st->pipe;
    return (0);
}

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
	st->firstcut = st->cutline;
    return (0);
}
