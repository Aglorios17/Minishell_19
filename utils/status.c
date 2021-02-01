/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	statusenv(shell *st, int status)
{
	char	*env;
	int		i;

	env = NULL;
	i = 0;
	while (st->envv)
	{
		env = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(env, "?=", 2))
		{
			i = 0;
			while (env[i] && env[i] != '=')
				i++;
			if (env[i] && env[i] == '=')
				i++;
			free((char *)st->envv->content);
			st->envv->content = ft_strjoin("?=", ft_itoa(status));
			st->envv = st->firstenv;
			return (status);
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("?=", ft_itoa(status))));
	st->envv = st->firstenv;
	return (status);
}
