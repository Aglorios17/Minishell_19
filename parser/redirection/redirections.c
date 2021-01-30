/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.ff>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:35:22 by gverhelp          #+#    #+#             */
/*   Updated: 2020/12/02 19:35:30 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ft_isinstring(char *str, char c)
{
	int a;

	a = 0;
	while (str[a])
	{
		if (str[a] == c)
			return (1);
		a++;
	}
	return (0);
}

int			ft_check_errorredir(shell *st)
{
	char *tokens;
	char *tokensnext;

	tokens = (char *)st->tokens->content;
	tokensnext = NULL;
	if (ft_check_errorredir2(tokens) == 1)
		return (1);
	if (ft_check_errorredir3(tokens) == 1)
		return (1);
	if (st->tokens->next)
	{
		tokensnext = (char *)st->tokens->next->content;
		if (ft_check_errorredir4(tokens, tokensnext) == 1)
			return (1);
		if (ft_check_errorredir5(tokensnext) == 1)
			return (1);
	}
	if (ft_check_errorredir6(tokens, tokensnext) == 1)
		return (1);
	return (0);
}

int			ft_check_redir(shell *st)
{
	st->redirnext = NULL;
	st->firsttok = st->tokens;
	while (st->tokens)
	{
		st->tokens = ft_redirections2(st, ">", ">>", "<");
		st->tokens = ft_redirections2(st, st->redirnext,
			st->redirnext, st->redirnext);
		st->redirnext = NULL;
	}
	st->tokens = st->firsttok;
	return (0);
}

int			ft_redirections_norme(shell *st)
{
	if (ft_check_redir(st) == 1)
		return (1);
	if (st->redir[0] != NULL)
	{
		if (ft_parse_redir(st) == 1)
			return (1);
	}
	return (0);
}

int			ft_redirections(shell *st)
{
	char	*tokens;

	tokens = NULL;
	if (!(st->redir = malloc(1 * sizeof(char *))))
		return (1);
	st->redir[0] = NULL;
	st->firsttok = st->tokens;
	while (st->tokens)
	{
		tokens = (char *)st->tokens->content;
		if (ft_isinstring("<>", tokens[0]) == 1)
		{
			if (ft_check_errorredir(st) == 1)
				return (1);
		}
		st->tokens = st->tokens->next;
	}
	st->tokens = st->firsttok;
	if (ft_redirections_norme(st) == 1)
		return (1);
	ft_freetab(st->redir);
	return (0);
}
