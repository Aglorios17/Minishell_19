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

int		getafterdol(t_dol *dol, char *tmp, int i)
{
	char	*fri;

	i++;
	while (tmp[i] && !ft_strchr("\'\"", tmp[i]) && tmp[i] != '\0')
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_' && tmp[i] != '?')
			break ;
		if (tmp[i] == '$' || tmp[i] == '\\')
			break ;
		fri = dol->nw;
		dol->nw = ft_charjoin(dol->nw, tmp[i]);
		free(fri);
		i++;
	}
	return (i);
}

int		ft_errordol(shell *st, t_dol *dol, int i)
{
	char	*fri;

	fri = NULL;
	if (dol->first[0] != '\0')
	{
		free(st->tmpq);
		st->tmpq = ft_strjoin(dol->first, "$");
	}
	else
	{
		fri = st->tmpq;
		st->tmpq = ft_charjoin(st->tmpq, '$');
		free(fri);
	}
	st->pass = i;
	return (0);
}

void	ft_initdol(shell *st, t_dol *dol)
{
	dol->cafter = 0;
	dol->nw = ft_strdup("");
	dol->first = ft_strdup("");
	dol->after = NULL;
	dol->backs = NULL;
	dol->nex = NULL;
	st->pass = 0;
	dol->env = NULL;
}

int		getfirstdol(t_dol *dol, char *tmp, int a, int i)
{
	char	*fri;

	fri = NULL;
	while (a < i)
	{
		fri = dol->first;
		dol->first = ft_charjoin(dol->first, tmp[a]);
		free(fri);
		a++;
	}
	return (0);
}

int		ft_dollars(shell *st, char *tmp, int i)
{
	char	*tmp2;
	t_dol	dol;

	ft_initdol(st, &dol);
	tmp2 = tmp;
	getfirstdol(&dol, tmp, 0, i);
	if (tmp[i + 1] == '\0' || tmp[i + 1] == '\\')
		return (ft_errordol(st, &dol, i));
	i = getafterdol(&dol, tmp, i);
	dol.after = ft_strdup(&tmp[i]);
	st->pass = i - 1;
	getvaluedol(st, &dol);
	if (!ft_strncmp(dol.nw, "SHLVL=", ft_strlen(dol.nw)))
		return (ft_shlvldol(st, &dol, tmp, i));
	else if (!ft_strncmp(dol.nw, "?=", ft_strlen(dol.nw)))
		return (ft_statusdol(st, &dol));
	else if (dol.env == NULL && !ft_strncmp("$OLDPWD", tmp2, 7))
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup("OLDPWD=")));
	else
		return (goretokens(st, &dol));
	freedol(&dol);
	return (1);
}
