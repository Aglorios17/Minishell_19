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

t_list		*ft_redirections2(shell *st, char *supp, char *supp2, char *supp3)
{
	t_list	*tmp;
	t_list	*previous;
	char	**redir;
	char	**fri;

	tmp = NULL;
	fri = NULL;
	previous = st->tokens;
	redir = malloc(2 * sizeof(char *));
	redir[0] = NULL;
	redir[1] = NULL;
	if (st->tokens == NULL || supp == NULL)
	{
		ft_freetab(redir);
		return (st->tokens);
	}
	if (!ft_strcmp((char *)previous->content, supp) ||
		!ft_strcmp((char *)previous->content, supp2) ||
		!ft_strcmp((char *)previous->content, supp3))
	{
		if (previous->next)
			st->redirnext = previous->next->content;
		st->tokens = previous->next;
		redir[0] = (char *)previous->content;
		redir[1] = NULL;
		fri = st->redir;
		st->redir = ft_tabjoin(st->redir, redir);
		free(fri);
		free(previous);
		st->firsttok = st->tokens;
//        ft_freetab(redir);
		return (st->tokens);
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (!ft_strcmp((char *)tmp->content, supp) ||
			!ft_strcmp((char *)tmp->content, supp2) ||
			!ft_strcmp((char *)tmp->content, supp3))
		{
			if (tmp->next)
				st->redirnext = tmp->next->content;
			redir[0] = (char *)previous->next->content;
			redir[1] = NULL;
			fri = st->redir;
			st->redir = ft_tabjoin(st->redir, redir);
			free(fri);
			previous->next = tmp->next;
			free(tmp);
//            ft_freetab(redir);
			return (st->tokens);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	ft_freetab(redir);
	return (0);
}