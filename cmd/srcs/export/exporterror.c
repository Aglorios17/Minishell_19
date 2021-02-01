/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int		ft_exporterror(shell *st, char *tmp)
{
	if (tmp[0] == '\0')
	{
		write(1, "minishell: export: `", 20);
		write(1, "': not a valid identifier\n", 26);
		st->status = 1;
		return (1);
	}
	if ((!ft_strchr(tmp, '=') && ft_strchr(tmp, ' ')) || tmp[0] == '=')
	{
		write(1, "minishell: export: `", 20);
		write(1, tmp, ft_strlen(tmp));
		write(1, "': not a valid identifier\n", 26);
		st->status = 1;
		return (1);
	}
	return (0);
}

int		ft_write_error(shell *st, char *tmp)
{
	write(1, "minishell: export: `", 20);
	write(1, tmp, ft_strlen(tmp));
	write(1, "': not a valid identifier\n", 26);
	st->status = 1;
	return (0);
}

int		ft_errorbefegal(shell *st, char *tmp)
{
	int		b;
	char	*bef;
	char	*fri;

	b = 0;
	fri = NULL;
	bef = ft_strdup("");
	while (tmp[b] && tmp[b] != '=')
	{
		fri = bef;
		bef = ft_charjoin(bef, tmp[b++]);
		free(fri);
	}
	if (ft_isdigit(bef[0]) || ft_strchr(bef, '\\') ||
		ft_strchr(bef, '\'') || ft_strchr(bef, '"') ||
		ft_strchr(bef, '$') || ft_strchr(bef, '|') ||
		ft_strchr(bef, ';') || ft_strchr(bef, '&') ||
		ft_strchr(bef, '!') || ft_strchr(bef, '@'))
	{
		ft_write_error(st, tmp);
		free(bef);
		return (1);
	}
	free(bef);
	return (0);
}

int		ft_errornoval(shell *st, char *tmp)
{
	int a;

	a = 0;
	while (tmp[a] != '=')
	{
		if (tmp[a] && tmp[a] == ' ')
		{
			ft_write_error(st, tmp);
			return (1);
		}
		a++;
	}
	if (tmp[a] && tmp[a - 1] && tmp[a] == '=' && tmp[a - 1] == ' ')
	{
		ft_write_error(st, tmp);
		return (1);
	}
	return (0);
}
