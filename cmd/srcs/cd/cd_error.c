/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	open_pathcd2(t_shell *st, char *path)
{
	if (errno == 20)
	{
		write(1, "minishell: ", 11);
		if (!ft_strcmp((char *)st->tokens->content, "cd\0"))
			write(1, "cd: ", 4);
		write(1, path, ft_strlen(path));
		write(1, ": Not a directory\n", 19);
		return (0);
	}
	if (errno == 13)
	{
		write(1, "minishell: ", 11);
		if (!ft_strcmp((char *)st->tokens->content, "cd\0"))
			write(1, "cd: ", 4);
		write(1, path, ft_strlen(path));
		write(1, ": Permission denied\n", 20);
		return (0);
	}
	return (1);
}

int	open_pathcd(t_shell *st, char *path)
{
	if (open_pathcd2(st, path) == 0)
		return (0);
	if (errno == 2)
	{
		if (!ft_strcmp((char *)st->tokens->content, "cd\0"))
		{
			write(1, "minishell: ", 11);
			write(1, "cd: ", 4);
			write(1, path, ft_strlen(path));
			write(1, ": No such file or directory\n", 28);
		}
		return (0);
	}
	return (1);
}

int	cdhomereturn(t_shell *st, char *line, char *tmp)
{
	if (chdir(line) < 0)
	{
		st->oldpwd = tmp;
		write(1, "minishell: ", 11);
		write(1, "cd: ", 4);
		write(1, "HOME not set\n", 13);
		if (line)
			free(line);
		st->status = 1;
		return (0);
	}
	st->pwd = ft_strdup(line);
	oldpwd(st);
	if (line)
		free(line);
	return (1);
}
