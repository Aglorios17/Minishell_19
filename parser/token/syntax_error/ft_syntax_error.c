/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_skip_quotes(t_shell *st, int a)
{
	if (st->line[a] == '"' || st->line[a] == '\'')
	{
		a++;
		while (st->line[a] && (st->line[a] != '"' || st->line[a] != '\''))
			a++;
	}
	if (st->line[a] == ';' || st->line[a] == '|')
	{
		if (st->line[a - 1] == '\\')
			a++;
	}
	return (a);
}

int	ft_verif_syntax2(t_shell *st)
{
	int a;

	a = 0;
	while (st->line[a])
	{
		a = ft_skip_quotes(st, a);
		if (st->line[a] == ';')
		{
			a++;
			if (ft_syntax_semicolon(st, a) == 1)
				return (1);
			while (st->line[a] == ' ')
				a++;
			if (ft_syntax_semicolon2(st, a) == 1)
				return (1);
		}
		if ((a = ft_syntax_pipe(st, a)) == -1)
			return (1);
		if (st->line[a])
			a++;
	}
	return (0);
}

int	ft_verif_syntax(t_shell *st)
{
	int		a;

	a = 0;
//	if (!st->line)
//		return (0);
	while (st->line[a] && st->line[a] == ' ')
		a++;
	if (st->line[a] && (st->line[a] == '<' || st->line[a] == '>'))
	{
		a = ft_syntax_redir(st, a);
		if (ft_syntax_redir2(st, a) == 1)
			return (1);
	}
	if (ft_syntax_redir3(st, a) == 1)
		return (1);
	if (ft_verif_syntax2(st) == 1)
		return (1);
	return (0);
}
