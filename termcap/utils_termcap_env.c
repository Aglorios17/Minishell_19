/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by gverhelp          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_termcap	*initglobalterm(void)
{
	static t_termcap tc;

	return (&tc);
}

char		*get_env_term(void)
{
	int			i;
	t_shell		*st;
	char		*env;
	char		*ret;

	i = 0;
	st = globalstruct();
	env = NULL;
	ret = NULL;
	while (st->envv)
	{
		env = (char *)st->envv->content;
		if (!ft_strncmp(env, "TERM=", 5))
		{
			i = 0;
			while (env[i] && env[i] != '=')
				i++;
			if (env[i] && env[i] == '=')
				i++;
			ret = ft_strdup(&env[i]);
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (ret);
}
