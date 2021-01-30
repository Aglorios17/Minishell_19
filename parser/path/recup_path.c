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

void	ft_freetab(char **tab)
{
	int a;

	a = 0;
	while (tab[a])
	{
		free(tab[a]);
		tab[a] = NULL;
		a++;
	}
	free(tab);
	tab = NULL;
}

char	*ft_path(shell *st, char *tmp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (tmp[i] != '=')
		i++;
	if (tmp[i] == '=')
		i++;
	path = ft_strdup(&tmp[i]);
	st->pat = ft_strdup(&tmp[i]);
	return (path);
}

char	*pathenv(shell *st)
{
	char	*tmp;
	char	*path;
	char	*cmppath;

	tmp = NULL;
	path = NULL;
	cmppath = ft_strdup("PATH=");
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(cmppath, tmp, ft_strlen(cmppath)))
		{
			path = ft_path(st, tmp);
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	free(cmppath);
	return (path);
}

char	**recuppath(shell *st, char **tab)
{
	char	*path;

	path = NULL;
	path = pathenv(st);
	tab = ft_split(path, ':');
	free(path);
	return (tab);
}
