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

#include "../../include/minishell.h"

void	freedol(t_dol *dol)
{
	free(dol->nw);
	free(dol->first);
	free(dol->after);
	free(dol->env);
}

int		getvaluedol(shell *st, t_dol *dol)
{
	char *fri;

	fri = dol->nw;
	dol->nw = ft_charjoin(dol->nw, '=');
	free(fri);
	while (st->envv)
	{
		dol->env = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(dol->nw, dol->env, ft_strlen(dol->nw)))
			break ;
		st->envv = st->envv->next;
		free(dol->env);
		dol->env = NULL;
	}
	st->envv = st->firstenv;
	return (0);
}

int		ft_statusdol(shell *st, t_dol *dol)
{
	free(st->tmpq);
	st->tmpq = ft_itoa(st->status);
	freedol(dol);
	return (1);
}

int		ft_shlvldol(shell *st, t_dol *dol, char *tmp, int i)
{
	int		a;
	char	*fri;

	fri = NULL;
	a = ft_atoi(&tmp[i]);
	free(st->tmpq);
	fri = ft_shlvl(&dol->env[i], a);
	st->tmpq = ft_strdup(&fri[6]);
	free(fri);
	freedol(dol);
	return (1);
}

int		goretokens(shell *st, t_dol *dol)
{
	if (dol->env == NULL)
		dol->env = ft_strdup("=");
	ft_retokens(st, dol);
	freedol(dol);
	return (1);
}
