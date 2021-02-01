/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_dollars(shell *st, char *tmp, int i)
{
	char	*new;
	char	*tmp2;
	char	*env;
	char	*first;
	char	*after;
	char	*fri;
	int		a;

	new = ft_strdup("");
	first = ft_strdup("");
	after = NULL;
	st->pass = 0;
	env = NULL;
	fri = NULL;
	a = 0;
	tmp2 = tmp;
	a = 0;
	while (a < i)
	{
		fri = first;
		first = ft_charjoin(first, tmp[a]);
		free(fri);
		a++;
	}
	if (tmp[i + 1] == '\0' || tmp[i + 1] == '\\')
	{
		if (first[0] != '\0')
		{
			free(st->tmpq);
			st->tmpq = ft_strjoin(first, "$");
		}
		else
		{
			fri = st->tmpq;
			st->tmpq = ft_charjoin(st->tmpq, '$');
			free(fri);
		}
		st->pass = i;
		return (0);
	}
	i++;
	while (tmp[i] && !ft_strchr("\'\"", tmp[i]) && tmp[i] != '\0')
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_' && tmp[i] != '?')
			break ;
		if (tmp[i] == '$' || tmp[i] == '\\')
			break ;
		fri = new;
		new = ft_charjoin(new, tmp[i]);
		free(fri);
		i++;
	}
	after = ft_strdup(&tmp[i]);
	st->pass = i - 1;
	fri = new;
	new = ft_charjoin(new, '=');
	free(fri);
	while (st->envv)
	{
		env = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(new, env, ft_strlen(new)))
			break ;
		st->envv = st->envv->next;
		free(env);
		env = NULL;
	}
	st->envv = st->firstenv;
	if (!ft_strncmp(new, "SHLVL=", ft_strlen(new)))
	{
		a = ft_atoi(&tmp[i]);
		free(st->tmpq);
		fri = ft_shlvl(&env[i], a);
		st->tmpq = ft_strdup(&fri[6]);
		free(fri);
	}
	else if (!ft_strncmp(new, "?=", ft_strlen(new)))
	{
		free(st->tmpq);
		st->tmpq = ft_itoa(st->status);
	}
	else if (env == NULL && !ft_strncmp("$OLDPWD", tmp2, 7))
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup("OLDPWD=")));
	else
	{
		if (env == NULL)
			env = ft_strdup("=");
		ft_retokens(st, env, first, after);
	}
	free(new);
	free(first);
	free(after);
	free(env);
	return (1);
}
