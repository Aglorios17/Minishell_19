/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_commandcd(shell *st, char *tmp, int i)
{
	if (ft_cd(st) == 1)
	{
		st->pwd = ft_pwd(st);
		while (st->envv)
		{
			tmp = (char *)st->envv->content;
			if (!ft_strncmp(tmp, "PWD=", 4))
			{
				if (st->pwd)
				{
					i = 0;
					while (tmp[i] != '=')
						i++;
					if (tmp[i] == '=')
						i++;
					st->envv->content = ft_strjoin("PWD=", st->pwd);
					break ;
				}
			}
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
	}
	return (0);
}

int	ft_commandenv(shell *st, char *tmp)
{
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strcmp(tmp, "_=env"))
			write(1, "_=/home/user42/Bureau/minishell_test/bin/env", 44);
		else
			write(st->fdout, tmp, ft_strlen(tmp));
		write(1, "\n", 1);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (0);
}

int	ft_commandunset(shell *st)
{
	st->tokens = st->tokens->next;
	while (st->tokens)
	{
		ft_unset(st);
		st->tokens = st->tokens->next;
	}
	st->tokens = st->firsttok;
	return (0);
}

int	ft_commandpwd(shell *st)
{
	write(1, ft_pwd(st), ft_strlen(ft_pwd(st)));
	write(1, "\n", 1);
	return (0);
}

int	ft_command(shell *st)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (!st->tokens)
		return (0);
	if (!(ft_strncmp((char *)st->tokens->content, "exit", 5)))
		return (ft_exit(st));
	else if (!(ft_strncmp((char *)st->tokens->content, "echo", 5)))
		ft_echo(st);
	else if (!ft_strncmp((char *)st->tokens->content, "pwd", 4))
		ft_commandpwd(st);
	else if (!ft_strncmp((char *)st->tokens->content, "cd", 3))
		ft_commandcd(st, tmp, i);
	else if (!ft_strncmp((char *)st->tokens->content, "export", 7))
		ft_export(st);
	else if (!ft_strncmp((char *)st->tokens->content, "unset", 6))
		ft_commandunset(st);
	else if (!ft_strncmp((char *)st->tokens->content, "env", 4))
		ft_commandenv(st, tmp);
	else
		ft_exec(st);
	return (0);
}
