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

char	*ft_traddollstr(shell *st, char *tmp2, char *re, int b)
{
	char *fri;

	fri = NULL;
	st->flagdq = 1;
	if (st->rd == 1)
		ft_dolredic(st, tmp2, b);
	else
		ft_dollars(st, tmp2, b);
	fri = re;
	re = ft_strjoin(re, st->tmpq);
	free(fri);
	st->flagdq = 0;
	return (re);
}

char	*ft_recheckstr(shell *st, char *tmp2, int b)
{
	char	*re;
	char	*fri;

	re = ft_strdup("");
	fri = NULL;
	while (tmp2 && tmp2[b])
	{
		if (tmp2[b] == '$')
		{
			re = ft_traddollstr(st, tmp2, re, b);
			b = st->pass;
		}
		else
		{
			if (tmp2[b] == '\\' && ft_strchr("\\$\"", tmp2[b + 1]))
				b++;
			fri = re;
			re = ft_charjoin(re, tmp2[b]);
			free(fri);
		}
		b++;
	}
	free(tmp2);
	return (re);
}

char	*newstr(char *tmp, int c, int b, int a)
{
	char *tmp2;

	tmp2 = NULL;
	if (((ft_back(tmp, b + 1)) % 2 == 0) || tmp[a - 1] != '\\')
	{
		free(tmp2);
		tmp2 = ft_substr(tmp, b + 1, c);
		return (tmp2);
	}
	return (NULL);
}

int		ft_double_quote(shell *st, char *tmp, int a)
{
	char	*tmp2;
	int		b;
	int		c;

	tmp2 = NULL;
	if (st->tmpq)
		free(st->tmpq);
	st->tmpq = ft_strdup("");
	b = a;
	c = 0;
	a++;
	st->quotes++;
	while (tmp[a])
	{
		if (tmp[a] == '"')
		{
			if ((tmp2 = newstr(tmp, c, b, a)) != NULL)
			{
				st->quotes++;
				break ;
			}
		}
		c++;
		a++;
	}
	tmp2 = ft_recheckstr(st, tmp2, 0);
	free(st->tmpq);
	st->tmpq = ft_strdup(tmp2);
	free(tmp2);
	return (a);
}
