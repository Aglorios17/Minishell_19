/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
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

int	ft_cmdexec(shell *st, char *cmd, struct stat b, char *tab)
{
	char	*tmp;
	char	*fri;

	tmp = NULL;
	fri = NULL;
	if (!ft_strchr(cmd, '/'))
	{
		if (ft_errorcmd(cmd) == 1)
			return (0);
		tmp = ft_strjoin(tab, "/");
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

int	check_path(shell *st, char *dollars)
{
	int			i;
	struct stat	b;
	char		**tab;

	tab = NULL;
	i = 0;
	if (dollars)
		dollars = NULL;
	if ((tab = recuppath(st, tab)) == NULL)
		return (0);
	free(st->cmdexec);
	st->cmdexec = ft_strdup((char *)st->tokens->content);
	while (tab[i])
	{
		if (ft_cmdexec(st, (char *)st->tokens->content, b, tab[i++]) == 1)
		{
			ft_freetab(tab);
			return (1);
		}
	}
	ft_freetab(tab);
	if (stat(st->cmdexec, &b) == -1)
		return (0);
	return (1);
}
