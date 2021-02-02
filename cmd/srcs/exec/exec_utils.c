/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*recupexp(shell *st)
{
	char	*tmp;

	tmp = NULL;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp("PATH=", tmp, 5))
			break ;
		st->envv = st->envv->next;
		tmp = NULL;
	}
	st->envv = st->envv;
	return (tmp);
}
