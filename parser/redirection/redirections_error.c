/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.ff>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:35:22 by gverhelp          #+#    #+#             */
/*   Updated: 2020/12/02 19:35:30 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_check_errorredir6(char *tokens, char *tokensnext)
{
	if (tokensnext == NULL && !ft_strncmp(tokens, "<<", 3))
	{
		ft_putstr("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (tokensnext == NULL && !ft_strncmp(tokens, "<<<", 4))
	{
		ft_putstr("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int			ft_check_errorredir5(char *tokensnext)
{
	if (!ft_strncmp(tokensnext, ">>", 2))
	{
		ft_putstr("minishell: syntax error near unexpected token `>>'\n");
		return (1);
	}
	if (!ft_strncmp(tokensnext, "<", 2))
	{
		ft_putstr("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	if (!ft_strncmp(tokensnext, "<<", 3))
	{
		ft_putstr("minishell: syntax error near unexpected token `<<'\n");
		return (1);
	}
	if (!ft_strncmp(tokensnext, "<<<", 3))
	{
		ft_putstr("minishell: syntax error near unexpected token `<<<'\n");
		return (1);
	}
	return (0);
}

int			ft_check_errorredir4(char *tokens, char *tokensnext)
{
	if ((ft_isinstring("<>", tokensnext[0]) == 0)
		&& !ft_strncmp(tokens, "<<", 3))
	{
		ft_putstr("minishell: syntax error near");
		ft_putstr(" unexpected token `newline'\n");
		return (1);
	}
	if ((ft_isinstring("<>", tokensnext[0]) == 0)
		&& !ft_strncmp(tokens, "<<<", 4))
	{
		ft_putstr("minishell: syntax error");
		ft_putstr(" near unexpected token `newline'\n");
		return (1);
	}
	if (!ft_strncmp(tokensnext, "<>", 2))
	{
		ft_putstr("minishell: syntax error near unexpected token `<>'\n");
		return (1);
	}
	if (!ft_strncmp(tokensnext, ">", 2))
	{
		ft_putstr("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	return (0);
}

int			ft_check_errorredir3(char *tokens)
{
	if (!ft_strncmp(tokens, "<<<<<", 6))
	{
		ft_putstr("minishell: syntax error near unexpected token `<<'\n");
		return (1);
	}
	if (!ft_strncmp(tokens, "<<<<<<", 6))
	{
		ft_putstr("minishell: syntax error near unexpected token `<<<'\n");
		return (1);
	}
	return (0);
}

int			ft_check_errorredir2(char *tokens)
{
	if (!ft_strncmp(tokens, "<>", 3))
	{
		ft_putstr("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (!ft_strncmp(tokens, ">>>", 4))
	{
		ft_putstr("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	if (!ft_strncmp(tokens, ">>>>", 4))
	{
		ft_putstr("minishell: syntax error near unexpected token `>>'\n");
		return (1);
	}
	if (!ft_strncmp(tokens, "<<<<", 5))
	{
		ft_putstr("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	return (0);
}
