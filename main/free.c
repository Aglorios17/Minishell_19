/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		ft_free_end(t_shell *st)
{
	free(st->line);
	free(st->pwd);
	free(st->pwdcp);
	free(st->oldpwd);
	free(st->tmpq);
	free(st->pat);
	free(st->cmdexec);
	free(st->new);
	if (st->pipe)
		ft_free_list(st->pipe, st->firstpipe);
	if (st->cutline)
		ft_free_list(st->cutline, st->firstcut);
	if (st->tokens)
		ft_free_list(st->tokens, st->firsttok);
	if (st->envv)
		ft_free_list(st->envv, st->firstenv);
	return (st->status);
}

int		ft_free_command(t_shell *st)
{
	free(st->line);
	st->line = NULL;
	free(st->tmpq);
	st->tmpq = NULL;
	free(st->pat);
	st->pat = NULL;
	if (st->tokens)
		ft_free_list(st->tokens, st->firsttok);
	st->tokens = NULL;
	return (st->status);
}
