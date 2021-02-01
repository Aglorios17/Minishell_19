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

int	ft_syntax_redir3(shell *st, int a)
{
	if (st->line[a] && (st->line[a] == ';' || st->line[a] == '|'))
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		if (st->line[a] == ';' && st->line[a + 1] == ';')
			write(2, ";;\'\n", 4);
		else if (st->line[a] == '|' && st->line[a + 1] == '|')
			write(2, "||\'\n", 4);
		else if (st->line[a] == ';')
			write(2, ";\'\n", 3);
		else if (st->line[a] == '|')
			write(2, "|\'\n", 3);
		st->status = 2;
		return (1);
	}
	return (0);
}

int	ft_syntax_redir2(shell *st, int a)
{
	if (st->line[a] == ';' || st->line[a] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		if (st->line[a] == ';')
			write(2, ";\'\n", 3);
		if (st->line[a] == '|')
			write(2, "|\'\n", 3);
		st->status = 2;
		return (1);
	}
	return (0);
}

int	ft_syntax_redir(shell *st, int a)
{
	if (st->line[a] == '>')
	{
		if (st->line[a + 1] != '>')
			a++;
		else if (st->line[a + 1] == '>')
			a += 2;
	}
	if (st->line[a] == '<')
	{
		if (st->line[a + 1] == '<' && st->line[a + 2] == '<')
			a += 3;
		else if (st->line[a + 1] == '<')
			a += 2;
		else if (st->line[a + 1] != '<')
			a++;
	}
	while (st->line[a] && st->line[a] == ' ')
		a++;
	return (a);
}
