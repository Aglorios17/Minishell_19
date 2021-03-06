/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_tabreturn(t_list *list)
{
	t_list	*tmp;
	char	**tabs;
	int		i;

	tabs = NULL;
	i = 0;
	tmp = list;
	if ((tabs = malloc(sizeof(char *) * (ft_lstsize(list) + 1))) == NULL)
		return (0);
	while (list)
	{
		tabs[i] = ft_strdup((char *)list->content);
		i++;
		list = list->next;
	}
	tabs[i] = NULL;
	list = tmp;
	return (tabs);
}

int		ft_checkcommand(t_shell *st)
{
	char *tmp;

	tmp = (char *)st->tokens->content;
	if (check_path(st, tmp) == 1)
		return (1);
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") ||
		!ft_strcmp(tmp, "pwd") || !ft_strcmp(tmp, "env") ||
		!ft_strcmp(tmp, "export") || !ft_strcmp(tmp, "unset") ||
		!ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}
