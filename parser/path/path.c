/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/09 14:57:25 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_errorcmd(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	ft_cmdexec(t_shell *st, char *cmd, char *tabs)
{
	char		*tmp;
	char		*fri;
	struct stat	b;

	tmp = NULL;
	fri = NULL;
	if (!ft_strchr(cmd, '/'))
	{
		if (ft_errorcmd(cmd) == 1)
			return (0);
		tmp = ft_strjoin(tabs, "/");
		fri = tmp;
		tmp = ft_strjoin(tmp, cmd);
		free(fri);
		if (stat(tmp, &b) != -1)
		{
			free(st->cmdexec);
			st->cmdexec = ft_strdup(tmp);
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int	check_path(t_shell *st, char *dollars)
{
	int			i;
	struct stat	b;
	char		**tabs;

	tabs = NULL;
	i = 0;
	if (dollars)
		dollars = NULL;
	if ((tabs = recuppath(st, tabs)) == NULL)
		return (0);
	free(st->cmdexec);
	st->cmdexec = ft_strdup((char *)st->tokens->content);
	while (tabs[i])
	{
		if (ft_cmdexec(st, (char *)st->tokens->content, tabs[i++]) == 1)
		{
			ft_freetab(tabs);
			return (1);
		}
	}
	ft_freetab(tabs);
	if (stat(st->cmdexec, &b) == -1)
		return (0);
	return (1);
}
