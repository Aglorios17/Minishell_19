/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cutpipe(shell *st)
{
	int		a;
	char	**line;

	a = 0;
	line = ft_splitms((char *)st->cutline->content, '|', st);
	while (line[a])
	{
		ft_lstadd_back(&st->pipe, ft_lstnew(ft_strdup(line[a])));
		a++;
	}
	st->firstpipe = st->pipe;
	ft_freetab(line);
	return (0);
}

int	ft_cutline(shell *st)
{
	int		a;
	char	**line;

	a = 0;
	if (ft_verif_syntax(st) == 1)
		return (1);
	if ((line = ft_splitms(st->line, ';', st)) == NULL)
		return (1);
	while (line[a])
	{
		ft_lstadd_back(&st->cutline, ft_lstnew(ft_strdup(line[a])));
		a++;
	}
	st->firstcut = st->cutline;
	ft_freetab(line);
	return (0);
}
