/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_traduction6(t_shell *st, char *tmp)
{
	char *fri;

	fri = NULL;
	fri = tmp;
	if (tmp[st->pass + 1])
		tmp = ft_strjoin(st->new, &tmp[st->pass + 1]);
	else
		tmp = ft_strdup(st->new);
	free(fri);
	return (tmp);
}

char	*ft_traduction5(t_shell *st, char *tmp)
{
	st->ret = 0;
	free(st->tmpq);
	st->tmpq = ft_strdup("");
	st->firstd++;
	if (st->rd == 0)
		ft_dollars(st, tmp, st->itrad);
	if (st->rd == 1)
		ft_dolredic(st, tmp, st->itrad);
	free(st->new);
	st->new = ft_strdup(st->tmpq);
	if (st->ret == 0)
		tmp = ft_traduction6(st, tmp);
	else
	{
		free(tmp);
		tmp = ft_strdup(st->new);
	}
	st->itrad = ft_strlen(st->new) - 1;
	return (tmp);
}

char	*ft_traduction4(t_shell *st, char *tmp, int b)
{
	char *back;
	char *fri;

	fri = NULL;
	back = NULL;
	back = ft_strdup("");
	while (b < st->itrad)
	{
		fri = back;
		back = ft_charjoin(back, tmp[b]);
		free(fri);
		b++;
	}
	fri = tmp;
	if (tmp[st->itrad + 1])
		tmp = ft_strjoin(back, &tmp[st->itrad + 1]);
	else
		tmp = ft_strdup(back);
	free(fri);
	free(back);
	return (tmp);
}
