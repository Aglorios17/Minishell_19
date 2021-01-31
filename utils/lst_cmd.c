/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	inenv(shell *st, char *tmp)
{
	int		a;
	char	*tmp2;

	a = 0;
	tmp2 = NULL;
	tmp2 = ft_strjoin("_=", tmp);
	while (st->envv)
	{
		if (!ft_strcmp((char *)st->envv->content, tmp2))
			a = 1;
		else if (!ft_strncmp((char *)st->envv->content, "_=", 2))
		{

			free((char *)st->envv->content);
			st->envv->content = ft_strdup(tmp2);
			a = 1;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup("_=/bin/bash")));
	st->envv = st->firstenv;
	free(tmp2);
	return (0);
}

int	error(shell *st, char *tmp)
{
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "=", 1))
			return (1);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (0);
}

int	lstcmd(shell *st, char *line)
{
	int		i;
	char	*tmp;
	char	*fri;

	i = 0;
	tmp = NULL;
	fri = NULL;
	if (error(st, line) == 1)
		return (0);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	tmp = ft_strdup("");
	while (line[i] && line[i] != ' ')
	{
		fri = tmp;
		tmp = ft_charjoin(tmp, line[i]);
		free(fri);
		i++;
	}
	inenv(st, tmp);
	free(tmp);
	return (1);
}
