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

int		ft_quotes(t_shell *st, char *tmp, int i)
{
	char	*fri;

	fri = NULL;
	if (tmp[i] == '"')
		i = ft_double_quote(st, tmp, i);
	else if (tmp[i] == '\'')
		i = ft_simple_quote(st, tmp, i);
	fri = st->new;
	st->new = ft_strjoin(st->new, st->tmpq);
	free(fri);
	return (i);
}

char	*ft_traduction3(t_shell *st, char *tmp)
{
	int		b;
	char	*fri;

	fri = NULL;
	b = 0;
	if (tmp[st->itrad] == '\\')
	{
		tmp = ft_traduction4(st, tmp, b);
		b = 1;
	}
	else if (tmp[st->itrad + 1] && (tmp[st->itrad] == '$' && b == 0 &&
		tmp[st->itrad + 1] != '\\' &&
		(ft_isalnum(tmp[st->itrad + 1]) || tmp[st->itrad + 1] == '_' ||
			tmp[st->itrad + 1] == '?')))
		tmp = ft_traduction5(st, tmp);
	else
	{
		fri = st->new;
		st->new = ft_charjoin(st->new, tmp[st->itrad]);
		free(fri);
	}
	return (tmp);
}

char	*ft_traduction2(t_shell *st, char *tmp)
{
	char	*fri;

	fri = NULL;
	st->itrad = ft_quotes(st, tmp, st->itrad);
	fri = tmp;
	if (tmp[st->itrad] && tmp[st->itrad + 1])
		tmp = ft_strjoin(st->new, &tmp[st->itrad + 1]);
	else
		tmp = ft_strdup(st->new);
	free(fri);
	st->itrad = ft_strlen(st->new) - 1;
	return (tmp);
}

void	ft_ifbackslash(t_shell *st)
{
	if (st->tmpq)
		free(st->tmpq);
	st->tmpq = ft_strdup("");
	if (st->new != NULL)
		free(st->new);
	st->new = ft_strdup("");
}

char	*ft_traduction(t_shell *st, char *tmp)
{
	st->itrad = 0;
	ft_ifbackslash(st);
	while (tmp[st->itrad] && tmp[st->itrad] != '\0')
	{
		if (tmp[st->itrad] == '"' || tmp[st->itrad] == '\'')
			tmp = ft_traduction2(st, tmp);
		else if (tmp[st->itrad] != '\0')
			tmp = ft_traduction3(st, tmp);
		st->itrad++;
	}
	free(st->new);
	st->new = NULL;
	return (tmp);
}
