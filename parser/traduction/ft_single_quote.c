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

int		ft_simple_quote(t_shell *st, char *tmp, int a)
{
	int b;
	int c;

	b = a;
	c = 0;
	a++;
	st->quotes2++;
	while (tmp[a])
	{
		if (tmp[a] == '\'')
		{
			free(st->tmpq);
			st->tmpq = ft_substr(tmp, b + 1, c);
			st->quotes2++;
			return (a);
		}
		c++;
		a++;
	}
	return (a);
}
