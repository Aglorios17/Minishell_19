/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_pwd(shell *st)
{
	st->pwd = getcwd(NULL, 0);
	return (st->pwd);
}

int		oldpwd(shell *st)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "OLDPWD=", 7))
		{
			i = 0;
			while (tmp[i] != '=')
				i++;
			if (tmp[i] == '=')
				i++;
			st->envv->content = ft_strjoin("OLDPWD=", st->oldpwd);
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (0);
}
