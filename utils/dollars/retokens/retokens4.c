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

int	ft_flagdq(shell *st, t_dol *dol, int a)
{
	free((char *)st->tokens->content);
	st->tokens->content = ft_strdup(&dol->env[a + 1]);
	free(st->tmpq);
	st->tmpq = ft_strdup((char *)st->tokens->content);
	free(dol->backs);
	return (1);
}

int	tradnull(shell *st, t_dol *dol, char **trad, int a)
{
	if (dol->first[0] != '\0')
	{
		free((char *)st->tokens->content);
		st->tokens->content = NULL;
		if (dol->env[a + 1] == ' ' && dol->after[0] != '\0')
		{
			free((char *)st->tokens->content);
			st->tokens->content = ft_strjoin(dol->first, " ");
		}
		else
		{
			free((char *)st->tokens->content);
			st->tokens->content = ft_strdup(dol->first);
		}
		free(st->tmpq);
		st->tmpq = ft_strdup((char *)st->tokens->content);
	}
	ft_freetab(trad);
	free(dol->backs);
	return (1);
}
