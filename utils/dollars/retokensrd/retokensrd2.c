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

void	ft_retokensrd7(t_retok *retok, t_shell *st)
{
	char	*fri;

	fri = NULL;
	if (retok->first[0] != '\0')
	{
		free(retok->tmp);
		retok->tmp = ft_strjoin(retok->first, retok->trad[0]);
		retok->a = 1;
	}
	if (retok->after[0] != '\0' && retok->trad[1] == NULL)
	{
		if (retok->first[0] == '\0')
			retok->tmp = retok->trad[0];
		retok->a = 1;
		fri = retok->trad[0];
		retok->trad[0] = ft_strjoin(retok->trad[0], retok->after);
		free(fri);
		st->pass += ft_strlen(retok->after);
	}
}

void	ft_retokensrd6(t_retok *retok, t_shell *st)
{
	char	*fri;

	fri = NULL;
	if (retok->first[0] != '\0')
	{
		retok->tmp = ft_strdup(retok->first);
		retok->a = 0;
		if (retok->after[0] != '\0' &&
			retok->env[ft_strlen(retok->env) - 1] != ' ')
		{
			fri = retok->trad[0];
			retok->trad[0] = ft_strjoin(retok->trad[0], retok->after);
			free(fri);
		}
	}
	else
	{
		retok->tmp = retok->trad[0];
		retok->a = 1;
	}
	st->ret = 1;
}

void	ft_retokensrd5_5(t_retok *retok, t_shell *st)
{
	char	*fri;

	fri = NULL;
	if (retok->first[0] == '\0')
		retok->tmp = retok->trad[0];
	else if (retok->first[0] != '\0')
	{
		free(retok->tmp);
		retok->tmp = ft_strjoin(retok->first, retok->trad[0]);
	}
	if (retok->after[0] != '\0')
	{
		fri = retok->trad[0];
		retok->trad[0] = ft_strjoin(retok->trad[0], retok->after);
		free(fri);
		st->pass += ft_strlen(retok->after);
	}
}

void	ft_retokensrd5(t_retok *retok, t_shell *st)
{
	if (retok->first[0] != '\0')
	{
		free(retok->tmp);
		retok->tmp = ft_strjoin(retok->first, retok->trad[0]);
		retok->a = 1;
	}
	if (retok->after[0] != '\0')
	{
		if (retok->trad[1] == NULL)
		{
			if (retok->first[0] != '\0')
			{
				free(retok->tmp);
				retok->tmp = ft_strjoin(retok->first, retok->trad[0]);
			}
			else
				retok->tmp = retok->trad[0];
		}
		else
			ft_retokensrd5_5(retok, st);
	}
}

int		ft_retokensrd4(t_retok *retok, t_shell *st)
{
	if (retok->first[0] != '\0')
	{
		if (retok->env[retok->a + 1] == ' ' && retok->after[0] != '\0')
			retok->tmp = ft_strjoin(retok->first, " ");
		else
			retok->tmp = retok->first;
		free(st->tmpq);
		st->tmpq = ft_strdup(retok->tmp);
	}
	ft_freetab(retok->trad);
	free(retok->backs);
	return (1);
}
