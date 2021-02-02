/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int		readdtok(t_shell *st, t_dol *dol, char **trad, int a)
{
	int c;

	c = 0;
	while (trad[c])
		c++;
	while (a < c && trad[a])
	{
		ft_lstadd_back(&st->tokens, ft_lstnew(ft_strdup(trad[a])));
		st->ddone += 1;
		a++;
	}
	if (dol->env[ft_strlen(dol->env) - 1] == ' ' && dol->after[0] != '\0')
		ft_lstadd_back(&st->tokens, ft_lstnew(ft_strdup(dol->after)));
	ft_lstadd_back(&st->tokens, dol->nex);
	ft_freetab(trad);
	free(dol->backs);
	return (1);
}

int		retok2first(t_shell *st, t_dol *dol, char **trad, int a)
{
	if (dol->first[0] != '\0')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strjoin(dol->first, trad[0]);
		a = 1;
	}
	return (a);
}

int		retok2tradunnull(t_shell *st, t_dol *dol, char **trad)
{
	free((char *)st->tokens->content);
	if (dol->first[0] != '\0')
		st->tokens->content = ft_strjoin(dol->first, trad[0]);
	else
		st->tokens->content = ft_strdup(trad[0]);
	return (0);
}

int		retok2tok(t_shell *st, t_dol *dol, char **trad)
{
	free((char *)st->tokens->content);
	if (dol->first[0] == '\0')
		st->tokens->content = ft_strdup(trad[0]);
	else if (dol->first[0] != '\0')
		st->tokens->content = ft_strjoin(dol->first, trad[0]);
	return (0);
}

char	*retok2cafter(t_dol *dol, char **trad, int a)
{
	char	*fri;

	fri = NULL;
	if (dol->cafter == 1)
	{
		fri = trad[a - 1];
		trad[a - 1] = ft_strjoin(trad[a - 1], dol->backs);
		free(fri);
	}
	else
	{
		fri = trad[a - 1];
		trad[a - 1] = ft_strjoin(trad[a - 1], " ");
		free(fri);
	}
	return (trad[a - 1]);
}
