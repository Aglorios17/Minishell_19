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

char	*ft_traduction(shell *st, char *tmp)
{
	int		i;
	int		b;
	char	*back;
	char	*fri;

	i = 0;
	b = 0;
	back = NULL;
	if (st->tmpq)
		free(st->tmpq);
	st->tmpq = ft_strdup("");
	fri = NULL;
	st->new = ft_strdup("");
	while (tmp[i] && tmp[i] != '\0')
	{
		if (tmp[i] == '"')
		{
			i = ft_double_quote(st, tmp, i);
			fri = st->new;
			st->new = ft_strjoin(st->new, st->tmpq);
			free(fri);
			tmp = ft_strjoin(st->new, &tmp[i + 1]);
			i = ft_strlen(st->new) - 1;
		}
		else if (tmp[i] == '\'')
		{
			i = ft_simple_quote(st, tmp, i);
			fri = st->new;
			st->new = ft_strjoin(st->new, st->tmpq);
			free(fri);
			tmp = ft_strjoin(st->new, &tmp[i + 1]);
			i = ft_strlen(st->new) - 1;
		}
		else if (tmp[i] != '\0')
		{
			b = 0;
			if (tmp[i] == '\\')
			{
				b = 0;
				back = ft_strdup("");
				while (b < i)
				{
					fri = back;
					back = ft_charjoin(back, tmp[b]);
					free(fri);
					b++;
				}
				tmp = ft_strjoin(back, &tmp[i + 1]);
				free(back);
				b = 1;
			}
			if (st->rd == 1 && (tmp[i] == '$' && b == 0 && tmp[i + 1] != '\\' &&
				(ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '_' || tmp[i + 1] == '?')))
			{
				st->ret = 0;
				free(st->tmpq);
				st->tmpq = ft_strdup("");
				st->firstd++;
				ft_dolredic(st, tmp, i);
				free(st->new);
				st->new = ft_strdup(st->tmpq);
				if (st->ret == 0)
					tmp = ft_strjoin(st->new, &tmp[st->pass + 1]);
				else
				{
					free(tmp);
					tmp = ft_strdup(st->new);
				}
				i = ft_strlen(st->new) - 1;
			}
			else if (st->rd == 0 && (tmp[i] == '$' && b == 0 && tmp[i + 1] != '\\' &&
				(ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '_' || tmp[i + 1] == '?')))
			{
				st->ret = 0;
				free(st->tmpq);
				st->tmpq = ft_strdup("");
				st->firstd++;
				ft_dollars(st, tmp, i);
				free(st->new);
				st->new = ft_strdup(st->tmpq);
				if (st->ret == 0)
				{
					tmp = ft_strjoin(st->new, &tmp[st->pass + 1]);
				}
				else
				{
					free(tmp);
					tmp = ft_strdup(st->new);
				}
				i = ft_strlen(st->new) - 1;
			}
			else
			{
				fri = st->new;
				st->new = ft_charjoin(st->new, tmp[i]);
				free(fri);
			}
		}
		i++;
	}
	free(st->new);
	return (tmp);
}
