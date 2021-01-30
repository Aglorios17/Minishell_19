#include "../include/minishell.h"

void	ft_free_list(t_list *list, t_list *first)
{
	t_list *tmp;

	list = first;
	first = NULL;
	while (list != NULL)
	{
		free(list->content);
		list->content = NULL;
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	list = NULL;
}



int	ft_exfree2(shell *st)
{
	if (st->pat)
	{
		free(st->pat);
		st->pat = NULL;
	}
	if (st->tmpq)
	{
		free(st->tmpq);
		st->tmpq = NULL;
	}
	if (st->line)
	{
		free(st->line);
		st->line = NULL;
	}
//	free(st->pwd);
	ft_free_list(st->tokens, st->firsttok);
	ft_free_list(st->envv, st->firstenv);
	if (st->status != 0)
		return (st->status);
	return (0);
}

int	ft_exfree(shell *st)
{
	if (st->pat)
	{
		free(st->pat);
		st->pat = NULL;
	}
	if (st->tmpq)
	{
		free(st->tmpq);
		st->tmpq = NULL;
	}
	if (st->line)
	{
		free(st->line);
		st->line = NULL;
	}
//	free(st->pwd);
	ft_free_list(st->tokens, st->firsttok);
	st->tokens = NULL;
	if (st->status != 0)
		return (st->status);	
	return (0);
}
