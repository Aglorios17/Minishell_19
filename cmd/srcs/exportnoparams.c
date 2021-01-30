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

#include "../../include/minishell.h"

char	*ft_lstenvchar(char *tmp, char *tmp2, int i)
{
	char *fri;

	fri = NULL;
	if (tmp[i] == '\0')
	{
		fri = tmp2;
		tmp2 = ft_charjoin(tmp2, '"');
		free(fri);
	}
	return (tmp2);
}

char	*ft_backenv(char *tmp, char *tmp2, int i)
{
	char *fri;

	fri = NULL;
	if (ft_strchr("\\\"$", tmp[i]))
		tmp2 = ft_charjoin(tmp2, '\\');
	fri = tmp2;
	tmp2 = ft_charjoin(tmp2, tmp[i]);
	free(fri);
	return (tmp2);
}

char	*ft_recupvalenv(shell *st, char *tmp, char *tmp2, char *fri)
{
	int i;
	int a;

	i = 0;
	a = 0;
	tmp = ft_strdup((char *)st->envv->content);
	tmp2 = ft_strdup("");
	while (tmp[i])
	{
		tmp2 = ft_backenv(tmp, tmp2, i);
		if (tmp[i] == '=' && !a)
		{
			fri = tmp2;
			tmp2 = ft_charjoin(tmp2, '"');
			free(fri);
			a = 1;
		}
		i++;
		tmp2 = ft_lstenvchar(tmp, tmp2, i);
	}
	return (tmp2);
}

int		ft_writenoparam(shell *st, char *tmp, char *tmp2, char *fri)
{
	tmp2 = ft_recupvalenv(st, tmp, tmp2, fri);
	write(1, "declare -x ", 11);
	write(1, tmp2, ft_strlen(tmp2));
	write(1, "\n", 1);
	free(tmp);
	free(tmp2);
	return (0);
}

int		ft_export_noparam(shell *st)
{
	char	*tmp;
	char	*fri;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	fri = NULL;
	while (st->envv->next)
	{
		ft_writenoparam(st, tmp, tmp2, fri);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (0);
}
