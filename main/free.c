#include "../include/minishell.h"

int	ft_exfree2(shell *st, t_list *tmp)
{
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
	st->tokens = st->firsttok;
	st->firsttok = NULL;
	while (st->tokens != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->tokens->content);
		st->tokens->content = NULL;
		tmp = st->tokens;
		st->tokens = st->tokens->next;
		free(tmp);
		tmp = NULL;
	}
	st->tokens = NULL;
	st->envv = st->firstenv;
	st->firstenv = NULL;
	while (st->envv != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->envv->content);
		st->envv->content = NULL;
		tmp = st->envv;
		st->envv = st->envv->next;
		free(tmp);
		tmp = NULL;
	}
	st->envv = NULL;
	if (st->status != 0)
		return (st->status);
	return (0);
}

int	ft_exfree(shell *st, t_list *tmp)
{
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
	st->tokens = st->firsttok;
	st->firsttok = NULL;
	while (st->tokens != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->tokens->content);
		st->tokens->content = NULL;
		tmp = st->tokens;
		st->tokens = st->tokens->next;
		free(tmp);
		tmp = NULL;
	}
	st->tokens = NULL;
	if (st->status != 0)
		return (st->status);	
	return (0);
}

int	ft_freecutline(shell *st, t_list *tmp)
{
	st->cutline = st->firstcut;
	st->firstcut = NULL;
	while (st->cutline != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->cutline->content);
		st->cutline->content = NULL;
		tmp = st->cutline;
		st->cutline = st->cutline->next;
		free(tmp);
		tmp = NULL;
	}
	st->cutline = NULL;
	return (0);
}


int	ft_freecutpipe(shell *st, t_list *tmp)
{
	st->pipe = st->firstpipe;
	st->firstpipe = NULL;
	while (st->pipe != NULL)
	{
		free(st->pipe->content);
		st->pipe->content = NULL;
		tmp = st->pipe;
		st->pipe = st->pipe->next;
		free(tmp);
		tmp = NULL;
	}
	st->pipe = NULL;
	return (0);
}
