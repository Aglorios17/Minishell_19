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

t_list		*ft_redirfirsttok(shell *st, t_list *previous)
{
	char	**redir;
	char	**fri;

	fri = NULL;
	redir = malloc(2 * sizeof(char *));
	redir[0] = NULL;
	redir[1] = NULL;
	if (previous->next)
		st->redirnext = (char *)previous->next->content;
	st->tokens = previous->next;
	redir[0] = (char *)previous->content;
	fri = st->redir;
	st->redir = ft_tabjoin(st->redir, redir);
	ft_freetab(fri);
	free(previous);
	st->firsttok = st->tokens;
	ft_freetab(redir);
	return (st->tokens);
}

t_list		*ft_redirtokens(shell *st, t_list *previous, t_list *tmp)
{
	char	**redir;
	char	**fri;

	fri = NULL;
	redir = malloc(2 * sizeof(char *));
	redir[0] = NULL;
	redir[1] = NULL;
	if (tmp->next)
		st->redirnext = (char *)tmp->next->content;
	redir[0] = (char *)tmp->content;
	fri = st->redir;
	st->redir = ft_tabjoin(st->redir, redir);
	ft_freetab(fri);
	previous->next = tmp->next;
	free(tmp);
	ft_freetab(redir);
	return (st->tokens);
}

t_list		*ft_redirections2(shell *st, char *supp, char *supp2, char *supp3)
{
	t_list	*tmp;
	t_list	*previous;

	tmp = NULL;
	previous = st->tokens;
	if (st->tokens == NULL || supp == NULL)
		return (st->tokens);
	if (!ft_strcmp((char *)previous->content, supp) ||
		!ft_strcmp((char *)previous->content, supp2) ||
		!ft_strcmp((char *)previous->content, supp3))
		return (ft_redirfirsttok(st, previous));
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (!ft_strcmp((char *)tmp->content, supp) ||
			!ft_strcmp((char *)tmp->content, supp2) ||
			!ft_strcmp((char *)tmp->content, supp3))
			return (ft_redirtokens(st, previous, tmp));
		previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}
