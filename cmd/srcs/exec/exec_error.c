/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_error4(shell *st, char *cmd, struct stat b)
{
	DIR		*dir;

	cmd = (char *)st->tokens->content;
	dir = opendir(cmd);
	if (dir != NULL || errno == 13)
	{
		closedir(dir);
		return (ft_directory_error2(st, 126));
	}
	else if (ft_strchr(cmd, '/') && stat(cmd, &b) == -1)
		return (ft_directory_error(st, 127));
	if (stat(cmd, &b) == 0)
	{
		if (!(b.st_mode & S_IRUSR && b.st_mode & S_IXUSR))
			return (ft_permission_error(st, 126, (char *)st->tokens->content));
	}
	return (1);
}

int	ft_directory_error(shell *st, int nb)
{
	write(2, "minishell: ", 11);
	write(2, (char *)st->tokens->content,
		ft_strlen((char *)st->tokens->content));
	write(2, ": No such file or directory\n", 28);
	st->status = nb;
	return (0);
}

int	ft_directory_error2(shell *st, int nb)
{
	write(2, "minishell: ", 11);
	write(2, (char *)st->tokens->content,
		ft_strlen((char *)st->tokens->content));
	write(2, ": is a directory\n", 17);
	st->status = nb;
	return (0);
}

int	ft_notfound_error(shell *st, int nb)
{
	write(2, "minishell: ", 11);
	write(2, (char *)st->tokens->content,
		ft_strlen((char *)st->tokens->content));
	write(2, ": command not found\n", 20);
	st->status = nb;
	return (0);
}

int	ft_permission_error(shell *st, int nb, char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": Permission denied\n", 20);
	st->status = nb;
	return (0);
}
