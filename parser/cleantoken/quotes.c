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

int		ft_cleantokens(t_shell *st)
{
	char	*newtok;

	st->quotes = 0;
	newtok = NULL;
	st->firstd = 1;
	st->ddone = 0;
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

int		ft_checkcommand(t_shell *st)
{
	char *tmp;

	tmp = (char *)st->tokens->content;
	if (check_path(st, tmp) == 1)
		return (1);
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") ||
		!ft_strcmp(tmp, "pwd") || !ft_strcmp(tmp, "env") ||
		!ft_strcmp(tmp, "export") || !ft_strcmp(tmp, "unset") ||
		!ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}
