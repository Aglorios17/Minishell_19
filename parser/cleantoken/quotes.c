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

int		ft_errorquote(t_shell *st)
{
	char	*fri;

	fri = NULL;
	if (st->quotes % 2 == 1)
	{
		fri = ft_strdup(
		"minishell: unexpected EOF while looking for matching `\"\'\n");
		write(1, fri, ft_strlen(fri));
		free(fri);
		st->status = 2;
		return (-1);
	}
	if (st->quotes2 % 2 == 1)
	{
		fri = ft_strdup(
		"minishell: unexpected EOF while looking for matching `\'\'\n");
		write(1, fri, ft_strlen(fri));
		free(fri);
		st->status = 2;
		return (-1);
	}
	st->quotes = 0;
	st->quotes2 = 0;
	return (1);
}

int		ft_lastcmdenv(t_shell *st, char *tmp2, char *fri)
{
	int	i;

	i = 0;
	if (!ft_strcmp((char *)st->firsttok->content, "export"))
	{
		free((char *)st->envv->content);
		st->envv->content = ft_strdup("");
		i = 0;
		while (tmp2[i] && tmp2[i] != '=')
		{
			fri = (char *)st->envv->content;
			st->envv->content = ft_charjoin((char *)st->envv->content, tmp2[i]);
			free(fri);
			i++;
		}
		fri = (char *)st->envv->content;
		st->envv->content = ft_strjoin("_=", (char *)st->envv->content);
		free(fri);
	}
	else
	{
		free((char *)st->envv->content);
		st->envv->content = ft_strjoin("_=", tmp2);
	}
	return (0);
}

int		ft_lastcmd(t_shell *st, char *fri)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	st->tokens = st->firsttok;
	while (st->tokens->next)
		st->tokens = st->tokens->next;
	tmp2 = (char *)st->tokens->content;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp("_=", tmp, 2))
		{
			ft_lastcmdenv(st, tmp2, fri);
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (0);
}

void	ft_initquotes(t_shell *st)
{
	st->firstd = 1;
	st->quotes = 0;
	st->quotes2 = 0;
	st->ddone = 0;
}

int		ft_cleantokens(t_shell *st)
{
	char	*newtok;

	newtok = NULL;
	ft_initquotes(st);
	while (st->tokens)
	{
		newtok = ft_traduction(st, ft_strdup((char *)st->tokens->content));
		free((char *)st->tokens->content);
		st->tokens->content = newtok;
		st->ddone += 1;
		while (st->tokens && st->ddone != 0)
		{
			st->tokens = st->tokens->next;
			st->ddone -= 1;
		}
	}
	if (ft_errorquote(st) == -1)
		return (-1);
	newtok = NULL;
	ft_lastcmd(st, newtok);
	st->tokens = st->firsttok;
	ft_checkcommand(st);
	return (0);
}
