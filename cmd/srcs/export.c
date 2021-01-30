/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_addexit(shell *st, char *tmp, char *tmp2, int i)
{
	int a;

	a = 0;
	if (!ft_strncmp(tmp, "SHLVL=", i))
	{
		a = ft_atoi(&tmp2[i]);
		st->envv->content = ft_shlvl(&tmp[i], a);
		a = 1;
	}
	else
	{
		if (!ft_strncmp(tmp, "PWD=", i))
			st->pwd = ft_strdup(&tmp[i]);
		if (!ft_strncmp(tmp, "OLDPWD=", i))
			st->oldpwd = ft_strdup(&tmp[i]);
		st->envv->content = ft_strdup(tmp);
		a = 1;
	}
	return (a);
}

int		ft_addinenv(shell *st, char *tmp, char *tmp2, int i)
{
	int a;

	a = 0;
	while (st->envv != NULL)
	{
		tmp2 = (char *)st->envv->content;
		i = 0;
		while (tmp2[i] != '=')
			i++;
		if (tmp2[i] == '=')
			i++;
		if (!ft_strncmp(tmp, tmp2, i))
			a = ft_addexit(st, tmp, tmp2, i);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(tmp)));
	st->tokens = st->tokens->next;
	return (0);
}

int		exportswitch(shell *st, char *tmp, int err)
{
	char	*tmp2;
	int		i;

	i = 0;
	tmp2 = NULL;
	if (err == 0)
		err = ft_errorbefegal(st, tmp);
	if (!ft_strchr(tmp, '=') && err == 0)
		err = 1;
	if (err == 0)
		err = ft_errornoval(st, tmp);
	if (err == 1)
		st->tokens = st->tokens->next;
	if (err == 0)
		ft_addinenv(st, tmp, tmp2, i);
	return (err);
}

int		ft_export(shell *st)
{
	char	*tmp;
	int		err;

	tmp = NULL;
	err = 0;
	if (st->pipe->next || st->pipe != st->firstpipe)
		return (0);
	if (!st->tokens->next)
		return (ft_export_noparam(st));
	st->tokens = st->tokens->next;
	while (st->tokens)
	{
		err = 0;
		tmp = (char *)st->tokens->content;
		err = ft_exporterror(st, tmp);
		err = exportswitch(st, tmp, err);
	}
	st->tokens = st->firsttok;
	return (0);
}
