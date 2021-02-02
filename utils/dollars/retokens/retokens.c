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

void	ft_cafter(t_dol *dol, int c, char *after)
{
	if (c != 0 && after[2] != '\0')
		c = 1;
	else
		c = 0;
	dol->cafter = c;
}

char	*ft_backs(t_dol *dol, int c, char *backs, char *after)
{
	char	*fri;

	fri = NULL;
	while (after[c] && ft_strchr(after, '\\'))
	{
		if (after[c] == '\\' && (after[c + 1] == ' ' || after[c + 1] == '\0'))
		{
			fri = backs;
			backs = ft_charjoin(backs, ' ');
			free(fri);
			c += 2;
		}
		else
		{
			if (after[c] == '\\' && after[c + 1] == '\\')
				c++;
			fri = backs;
			backs = ft_charjoin(backs, after[c]);
			free(fri);
			c++;
		}
	}
	ft_cafter(dol, c, after);
	return (backs);
}

void	ft_retokinit(t_shell *st, t_dol *dol)
{
	dol->cafter = 0;
	if (st->tmpq)
		free(st->tmpq);
	st->tmpq = ft_strdup("");
	dol->nex = NULL;
	dol->backs = ft_backs(dol, 0, ft_strdup(""), dol->after);
	st->ddone = 0;
}

int		ft_retokens(t_shell *st, t_dol *dol)
{
	int		a;
	char	**trad;

	a = 0;
	ft_retokinit(st, dol);
	trad = NULL;
	while (dol->env[a] && dol->env[a] != '=')
		a++;
	if (st->flagdq == 0 && dol->env[a])
		trad = ft_split(&dol->env[a + 1], ' ');
	else if (st->flagdq == 1)
		return (ft_flagdq(st, dol, a));
	if (trad[0] == NULL)
		return (tradnull(st, dol, trad, a));
	if (st->tokens->next)
	{
		dol->nex = st->tokens->next;
		st->tokens->next = NULL;
	}
	a = switchretok(st, dol, trad, a);
	free(st->tmpq);
	st->tmpq = ft_strdup((char *)st->tokens->content);
	return (readdtok(st, dol, trad, a));
}
