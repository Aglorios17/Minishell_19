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

int	ft_syntax_pipe3(t_shell *st, int a, int flagspace)
{
	if (st->line[a] == '|' && flagspace == 0)
	{
		if (st->line[a + 1] == '|' && st->line[a + 2] == '|')
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, "||\'\n", 4);
			st->status = 2;
			return (1);
		}
		if (st->line[a + 1] == '|')
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, "|\'\n", 3);
			st->status = 2;
			return (1);
		}
	}
	return (0);
}

int	ft_syntax_pipe2(t_shell *st, int a, int flagspace)
{
	if (!st->line[a])
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, "|\'\n", 3);
		st->status = 2;
		return (1);
	}
	if (st->line[a] == ';')
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, ";\'\n", 3);
		st->status = 2;
		return (1);
	}
	if (st->line[a] == '|' && flagspace == 1)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, "|\'\n", 3);
		st->status = 2;
		return (1);
	}
	return (0);
}

int	ft_syntax_pipe(t_shell *st, int a)
{
	int	flagspace;

	flagspace = 0;
	if (st->line[a] == '|')
	{
		a++;
		while (st->line[a] == ' ')
		{
			flagspace = 1;
			a++;
		}
		if (ft_syntax_pipe2(st, a, flagspace) == 1)
			return (-1);
		if (ft_syntax_pipe3(st, a, flagspace) == 1)
			return (-1);
	}
	return (a);
}

int	ft_syntax_semicolon2(t_shell *st, int a)
{
	if (st->line[a] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, "|\'\n", 3);
		st->status = 2;
		return (1);
	}
	if (st->line[a] == ';')
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, ";\'\n", 3);
		st->status = 2;
		return (1);
	}
	return (0);
}

int	ft_syntax_semicolon(t_shell *st, int a)
{
	if (st->line[a] == ';')
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, ";;\'\n", 4);
		st->status = 2;
		return (1);
	}
	return (0);
}
