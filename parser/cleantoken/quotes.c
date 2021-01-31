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

int		ft_cleantokens(shell *st)
{
	char	*tmp;
	char	*tmp2;
	char	*fri;
	int		i;

	st->quotes = 0;
	i = 0;
	tmp = 0;
	tmp2 = 0;
	fri = NULL;
	st->firstd = 1;
	st->ddone = 0;
	st->firsttok = st->tokens;
	tmp = ft_strdup((char*)st->tokens->content);
	fri = ft_strdup(ft_traduction(st, tmp));
	free(tmp);
	free((char *)st->tokens->content);
	st->tokens->content = fri;
	if (!st->tokens->next)
	{
		while (st->envv)
		{
			tmp = (char *)st->envv->content;
			if (!ft_strncmp("_=", tmp, 2))
			{
				free((char *)st->envv->content);
				st->envv->content = ft_strjoin("_=", (char *)st->tokens->content);
				break ;
			}
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
	}	
	if (!(ft_checkcommand(st)))
		return (0);
	if (!st->tokens->next)
		return (0);
	st->tokens = st->tokens->next;
	while (st->tokens)
	{
		tmp = ft_strdup((char *)st->tokens->content);
		fri = ft_strdup(ft_traduction(st, tmp));
		free(tmp);
		free((char *)st->tokens->content);
		st->tokens->content = fri;
		tmp2 = (char *)st->tokens->content;
		st->ddone += 1;
		while (st->tokens && st->ddone != 0)
		{
			st->tokens = st->tokens->next;
			st->ddone -= 1;
		}
	}
	if (st->quotes % 2 == 1)
	{
		fri = ft_strdup("minishell: unexpected EOF while looking for matching `\"\'\n");
		write(1, fri, ft_strlen(fri));
		free(fri);
		st->status = 2;
		return (-1);
	}
	if (st->quotes2 % 2 == 1)
	{
		fri = ft_strdup("minishell: unexpected EOF while looking for matching `\'\'\n");
		write(1, fri, ft_strlen(fri));
		free(fri);
		st->status = 2;
		return (-1);
	}
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp("_=", tmp, 2))
		{
			if (!ft_strcmp((char *)st->firsttok->content, "export"))
			{
				st->envv->content = ft_strdup("");
				i = 0;
				while (tmp2[i] && tmp2[i] != '=')
				{
					fri = (char *)st->envv->content;
					st->envv->content = ft_charjoin((char *)st->envv->content, tmp2[i]);
					free(fri);
					i++;
				}
				st->envv->content = ft_strjoin("_=", (char *)st->envv->content);
			}
			else
			{
				free((char *)st->envv->content);
				st->envv->content = ft_strjoin("_=", tmp2);
			}
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	st->tokens = st->firsttok;
	return (0);
}

int	ft_checkcommand(shell *st)
{
	char *tmp;

	tmp = (char *)st->tokens->content;
	if (check_path(st, tmp) == 1)
		return (1);
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "env") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}
