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

void	ft_init_retok2(t_retok *retok, char *tmp)
{
	retok->a = 0;
	retok->b = 0;
	retok->trad = NULL;
	retok->backs = ft_strdup("");
	retok->tmp = tmp;
}

int		ft_retokensrd3(t_retok *retok, t_shell *st)
{
	while (retok->env[retok->a] && retok->env[retok->a] != '=')
		retok->a++;
	if (st->flagdq == 0 && retok->env[retok->a])
	{
		retok->trad = ft_split(&retok->env[retok->a + 1], ' ');
		if (retok->trad[1] != NULL && st->flagdq == 0)
		{
			write(2, "minishell: ", 11);
			write(2, retok->tmp, ft_strlen(retok->tmp));
			write(2, ": ambiguous redirect\n", 21);
			free(retok->backs);
			ft_freetab(retok->trad);
			return (1);
		}
	}
	else if (st->flagdq == 1)
	{
		retok->tmp = &retok->env[retok->a + 1];
		free(st->tmpq);
		st->tmpq = ft_strdup(retok->tmp);
		free(retok->backs);
		return (1);
	}
	return (0);
}

void	ft_retokensrd2(t_retok *retok)
{
	char *fri;

	fri = NULL;
	while (retok->after[retok->b] && ft_strchr(retok->after, '\\'))
	{
		if (retok->after[retok->b] == '\\' &&
			(retok->after[retok->b + 1] == ' ' ||
			retok->after[retok->b + 1] == '\0'))
		{
			fri = retok->backs;
			retok->backs = ft_charjoin(retok->backs, ' ');
			free(fri);
			retok->b += 2;
		}
		else
		{
			if (retok->after[retok->b] == '\\' &&
				retok->after[retok->b + 1] == '\\')
				retok->b++;
			fri = retok->backs;
			retok->backs = ft_charjoin(retok->backs, retok->after[retok->b]);
			free(fri);
			retok->b++;
		}
	}
}

int		ft_retokensrdpart2(t_retok *retok, t_shell *st)
{
	if (retok->trad[0] == NULL)
		return (ft_retokensrd4(retok, st));
	if (retok->first[0] == '\0' && retok->after[0] == '\0' &&
		retok->env[retok->a + 1] != ' ' &&
		retok->env[ft_strlen(retok->env) - 1] != ' ')
	{
		retok->tmp = retok->trad[0];
		retok->a = 1;
	}
	else if (retok->env[retok->a + 1] != ' ' &&
		retok->env[ft_strlen(retok->env) - 1] != ' ')
		ft_retokensrd5(retok, st);
	else if (retok->first[0] == '\0' && retok->after[0] == '\0' &&
		retok->env[retok->a + 1] == ' ' &&
		retok->env[ft_strlen(retok->env) - 1] == ' ')
	{
		retok->tmp = retok->trad[0];
		retok->a = 1;
	}
	else if (retok->env[retok->a + 1] == ' ')
		ft_retokensrd6(retok, st);
	else if (retok->env[retok->a + 1] != ' ' &&
		retok->env[ft_strlen(retok->env) - 1] == ' ')
		ft_retokensrd7(retok, st);
	return (0);
}

int		ft_retokensrd(t_shell *st, char *lol, t_retok *retok)
{
	char	*fri;

	fri = NULL;
	(void)fri;
	ft_init_retok2(retok, lol);
	if (st->tmpq)
		free(st->tmpq);
	st->tmpq = ft_strdup("");
	ft_retokensrd2(retok);
	retok->b = 0;
	st->ddone = 0;
	if (ft_retokensrd3(retok, st) == 1)
		return (1);
	if (ft_retokensrdpart2(retok, st) == 1)
		return (1);
	free(st->tmpq);
	st->tmpq = ft_strdup(retok->tmp);
	ft_freetab(retok->trad);
	free(retok->backs);
	return (1);
}
