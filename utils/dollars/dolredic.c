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

#include "../../include/minishell.h"

int	ft_retokensrd(shell *st, char *env, char *first, char *after, char *tmp)
{
	int		a;
	int		b;
	char	**trad;
	char	*backs;

	a = 0;
	b = 0;
	trad = NULL;
	backs = ft_strdup("");
	while (after[b] && ft_strchr(after, '\\'))
	{
		if (after[b] == '\\' && (after[b + 1] == ' ' || after[b + 1] == '\0'))
		{
			backs = ft_charjoin(backs, ' ');
			b += 2;
		}
		else
		{
			if (after[b] == '\\' && after[b + 1] == '\\')
				b++;
			backs = ft_charjoin(backs, after[b]);
			b++;
		}
	}
	b = 0;
	st->ddone = 0;
	while (env[a] && env[a] != '=')
		a++;
	if (st->flagdq == 0 && env[a])
	{
		trad = ft_split(&env[a + 1], ' ');
		if (trad[1] != NULL && st->flagdq == 0)
		{
			write(2, "minishell: ", 11);
			write(2, tmp, ft_strlen(tmp));
			write(2, ": ambiguous redirect\n", 21);
			free(backs);
			return (1);
		}
	}
	else if (st->flagdq == 1)
	{
		tmp = ft_strdup(&env[a + 1]);
		st->tmpq = ft_strdup(tmp);
		free(backs);
		return (1);
	}
	if (trad[0] == NULL)
	{
		if (first[0] != '\0')
		{
			if (env[a + 1] == ' ' && after[0] != '\0')
				tmp = ft_strjoin(first, " ");
			else
				tmp = ft_strdup(first);
			st->tmpq = ft_strdup((char *)st->tokens->content);
		}
		free(backs);
		return (1);
	}
	if (first[0] == '\0' && after[0] == '\0' &&
		env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
	{
		tmp = ft_strdup(trad[0]);
		a = 1;
	}
	else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
	{
		if (first[0] != '\0')
		{
			tmp = ft_strjoin(first, trad[0]);
			a = 1;
		}
		if (after[0] != '\0')
		{
			if (trad[1] == NULL)
			{
				if (first[0] != '\0')
					tmp = ft_strjoin(first, trad[0]);
				else
					tmp = ft_strdup(trad[0]);
			}
			else
			{
				if (first[0] == '\0')
					tmp = ft_strdup(trad[0]);
				else if (first[0] != '\0')
					tmp = ft_strjoin(first, trad[0]);
				if (after[0] != '\0')
				{
					trad[0] = ft_strjoin(trad[0], after);
					st->pass += ft_strlen(after);
				}
			}
		}
	}
	else if (first[0] == '\0' && after[0] == '\0' &&
		env[a + 1] == ' ' && env[ft_strlen(env) - 1] == ' ')
	{
		tmp = ft_strdup(trad[0]);
		a = 1;
	}
	else if (env[a + 1] == ' ')
	{
		if (first[0] != '\0')
		{
			tmp = ft_strdup(first);
			a = 0;
			if (after[0] != '\0' && env[ft_strlen(env) - 1] != ' ')
				trad[0] = ft_strjoin(trad[0], after);
		}
		else
		{
			tmp = ft_strdup(trad[0]);
			a = 1;
		}
		st->ret = 1;
	}
	else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] == ' ')
	{
		if (first[0] != '\0')
		{
			tmp = ft_strjoin(first, trad[0]);
			a = 1;
		}
		if (after[0] != '\0' && trad[1] == NULL)
		{
			if (first[0] == '\0')
				tmp = ft_strdup(trad[0]);
			a = 1;
			trad[0] = ft_strjoin(trad[0], after);
			st->pass += ft_strlen(after);
		}
	}
	st->tmpq = ft_strdup(tmp);
	free(backs);
	return (1);
}

int	ft_dolredic(shell *st, char *tmp, int i)
{
	char	*new;
	char	*space;
	char	*tmp2;
	char	*env;
	char	*first;
	char	*after;
	int		a;

	new = ft_strdup("");
	first = ft_strdup("");
	after = NULL;
	st->pass = 0;
	space = NULL;
	env = NULL;
	a = 0;
	(void)tmp2;
	(void)space;
	tmp2 = tmp;
	a = 0;
	while (a < i)
	{
		first = ft_charjoin(first, tmp[a]);
		a++;
	}
	if (tmp[i + 1] == '\0' || tmp[i + 1] == '\\')
	{
		if (first[0] != '\0')
			st->tmpq = ft_strjoin(first, "$");
		else
			st->tmpq = ft_charjoin(st->tmpq, '$');
		st->pass = i;
		return (0);
	}
	i++;
	while (tmp[i] && !ft_strchr("\'\"", tmp[i]) && tmp[i] != '\0')
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_' && tmp[i] != '?')
			break ;
		if (tmp[i] == '$' || tmp[i] == '\\')
		{
			if (tmp[i] == '\\' && !tmp[i + 1])
				space = ft_strdup(" ");
			break ;
		}
		new = ft_charjoin(new, tmp[i]);
		i++;
	}
	after = ft_strdup(&tmp[i]);
	st->pass = i - 1;
	new = ft_charjoin(new, '=');
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
		st->tmpq = ft_strdup(&ft_shlvl(&env[i], a)[6]);
	}
	else if (!ft_strncmp(new, "?=", ft_strlen(new)))
		st->tmpq = ft_itoa(st->status);
	else if (env == NULL && !ft_strncmp("$OLDPWD", tmp2, 7))
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("OLDPWD=", "")));
	else
	{
		if (env == NULL)
			env = ft_strdup("=");
		ft_retokensrd(st, env, first, after, tmp);
	}
	return (1);
}
