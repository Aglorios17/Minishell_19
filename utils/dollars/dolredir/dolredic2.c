/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolredic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_dolredir6(t_retok *retok, t_shell *st, char *tmp)
{
	char	*fri;

	fri = NULL;
	if (!ft_strncmp(retok->new, "SHLVL=", ft_strlen(retok->new)))
	{
		retok->a = ft_atoi(&tmp[retok->count]);
		free(st->tmpq);
		fri = ft_shlvl(&retok->env[retok->count], retok->a);
		st->tmpq = ft_strdup(&fri[6]);
		free(fri);
	}
	else if (!ft_strncmp(retok->new, "?=", ft_strlen(retok->new)))
	{
		free(st->tmpq);
		st->tmpq = ft_itoa(st->status);
	}
	else if (retok->env == NULL && !ft_strncmp("$OLDPWD", retok->tmp2, 7))
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("OLDPWD=", "")));
	else
	{
		if (retok->env == NULL)
			retok->env = ft_strdup("=");
		ft_retokensrd(st, tmp, retok);
	}
}

void	ft_dolredir5(t_retok *retok, t_shell *st)
{
	while (st->envv)
	{
		retok->env = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(retok->new, retok->env, ft_strlen(retok->new)))
			break ;
		st->envv = st->envv->next;
		free(retok->env);
		retok->env = NULL;
	}
	st->envv = st->firstenv;
}
