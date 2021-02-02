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

int			ft_parse_redir4(t_shell *st, int a)
{
	if (!ft_strcmp(st->redir[a], "<"))
	{
		if ((st->fdredir = open(st->redir[a + 1], O_RDONLY)) < 0)
		{
			if (errno == 2)
			{
				write(2, "minishell: ", 11);
				write(2, st->redir[a + 1], ft_strlen(st->redir[a + 1]));
				write(2, ": No such file or directory\n", 28);
			}
			if (errno == 13)
			{
				write(2, "minishell: ", 11);
				write(2, st->redir[a + 1], ft_strlen(st->redir[a + 1]));
				write(2, ": Permission denied\n", 20);
			}
			return (1);
		}
	}
	return (0);
}

int			ft_parse_redir3(t_shell *st, int a)
{
	if (st->redir[1] == NULL)
	{
		ft_putstr("minishell: syntax error near");
		ft_putstr(" unexpected token `newline'\n");
		st->status = 2;
		return (1);
	}
	if (!ft_strcmp(st->redir[a], ">"))
	{
		if ((st->fdredir = open(st->redir[a + 1], O_WRONLY |
			O_CREAT | O_TRUNC, 0644)) < 0)
			return (1);
	}
	if (!ft_strcmp(st->redir[a], ">>"))
	{
		if ((st->fdredir = open(st->redir[a + 1], O_WRONLY |
			O_APPEND | O_CREAT, 0644)) < 0)
			return (1);
	}
	return (0);
}

void		ft_parse_redir2(t_shell *st, int a)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (st->redir[a + 1])
	{
		tmp = st->redir[a + 1];
		i = ft_strlen(tmp);
		while (tmp[i - 1] == ' ')
			i--;
		tmp = ft_substr(tmp, 0, i);
		new = ft_traduction(st, tmp);
		free(st->redir[a + 1]);
		st->redir[a + 1] = new;
	}
}

int			ft_parse_redir0(t_shell *st, int a)
{
	while (st->redir[a])
	{
		if (ft_parse_redir3(st, a) == 1)
			return (1);
		if (ft_parse_redir4(st, a) == 1)
			return (1);
		a++;
	}
	return (0);
}

int			ft_parse_redir(t_shell *st)
{
	int		a;
	char	*tmp2;

	a = 0;
	st->fdredir = 1;
	tmp2 = NULL;
	st->rd = 1;
	ft_parse_redir2(st, a);
	tmp2 = ft_strdup(st->redir[a]);
	st->rd = 0;
	if (ft_parse_redir0(st, a) == 1)
	{
		free(tmp2);
		return (1);
	}
	if (!ft_strcmp(tmp2, "<"))
		st->fdout = dup2(st->fdredir, 0);
	else
		st->fdout = dup2(st->fdredir, 1);
	st->fdredir = 0;
	free(tmp2);
	return (0);
}
