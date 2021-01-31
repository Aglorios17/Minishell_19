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

int	ft_cmddollars(shell *st, char *tmp)
{
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

int	ft_retokens(shell *st, char *env, char *first, char *after)
{
	int		a;
	int		b;
	int		c;
	char	**trad;
	char	*backs;
	char	*fri;
	t_list	*nex;

	a = 0;
	b = 0;
	c = 0;
	trad = NULL;
	if (st->tmpq)
		free(st->tmpq);
	st->tmpq = ft_strdup("");
	backs = ft_strdup("");
	nex = NULL;
	fri = NULL;
	while (after[b] && ft_strchr(after, '\\'))
	{
		if (after[b] == '\\' && (after[b + 1] == ' ' || after[b + 1] == '\0'))
		{
			fri = backs;
			backs = ft_charjoin(backs, ' ');
			free(fri);
			b += 2;
		}
		else
		{
			if (after[b] == '\\' && after[b + 1] == '\\')
				b++;
			fri = backs;
			backs = ft_charjoin(backs, after[b]);
			free(fri);
			b++;
		}
	}
	if (b != 0 && after[2] != '\0')
		c = 1;
	b = 0;
	st->ddone = 0;
	while (env[a] && env[a] != '=')
		a++;
	if (st->flagdq == 0 && env[a])
		trad = ft_split(&env[a + 1], ' ');
	else if (st->flagdq == 1)
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(&env[a + 1]);
		free(st->tmpq);
		st->tmpq = ft_strdup((char *)st->tokens->content);
		free(backs);
		return (1);
	}
	if (trad[0] == NULL)
	{
		if (first[0] != '\0')
		{
			free((char *)st->tokens->content);
			st->tokens->content = NULL;
			if (env[a + 1] == ' ' && after[0] != '\0')
			{
				free((char *)st->tokens->content);
				st->tokens->content = ft_strjoin(first, " ");
			}
			else
			{
				free((char *)st->tokens->content);
				st->tokens->content = ft_strdup(first);
			}
			free(st->tmpq);
			st->tmpq = NULL;
			st->tmpq = ft_strdup((char *)st->tokens->content);
		}
		ft_freetab(trad);
		free(backs);
		return (1);
	}
	if (st->tokens->next)
	{
		nex = st->tokens->next;
		st->tokens->next = NULL;
	}
	if (first[0] == '\0' && after[0] == '\0' &&
		env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(trad[0]);
		a = 1;
	}
	else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
	{
		if (first[0] != '\0')
		{
			free((char *)st->tokens->content);
			st->tokens->content = ft_strjoin(first, trad[0]);
			a = 1;
		}
		if (after[0] != '\0')
		{
			if (trad[1] == NULL)
			{
				free((char *)st->tokens->content);
				if (first[0] != '\0')
					st->tokens->content = ft_strjoin(first, trad[0]);
				else
					st->tokens->content = ft_strdup(trad[0]);
			}
			else
			{
				free((char *)st->tokens->content);
				if (first[0] == '\0')
					st->tokens->content = ft_strdup(trad[0]);
				else if (first[0] != '\0')
					st->tokens->content = ft_strjoin(first, trad[0]);
				if (after[0] != '\0')
				{
					a = 1;
					b = 0;
					while (trad[b])
						b++;
					if (after[0] == '\\')
					{
						if (c == 1)
						{
							fri = trad[b - 1];
							trad[b - 1] = ft_strjoin(trad[b - 1], backs);
							free(fri);
						}
						else
						{
							fri = trad[b - 1];
							trad[b - 1] = ft_strjoin(trad[b - 1], " ");
							free(fri);
						}
					}
					else
					{
						fri = trad[b - 1];
						trad[b - 1] = ft_strjoin(trad[b - 1], after);
						free(fri);
					}
					st->pass += ft_strlen(after);
				}
			}
		}
	}
	else if (first[0] == '\0' && after[0] == '\0' &&
		env[a + 1] == ' ' && env[ft_strlen(env) - 1] == ' ')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(trad[0]);
		a = 1;
	}
	else if (env[a + 1] == ' ')
	{
		if (first[0] != '\0')
		{
			free((char *)st->tokens->content);
			st->tokens->content = ft_strdup(first);
			a = 0;
			if (after[0] != '\0' && env[ft_strlen(env) - 1] != ' ')
			{
				b = 0;
				while (trad[b])
					b++;
				fri = trad[b - 1];
				trad[b - 1] = ft_strjoin(trad[b - 1], after);
				free(fri);
			}
		}
		else
		{
			free((char *)st->tokens->content);
			st->tokens->content = ft_strdup(trad[0]);
			a = 1;
		}
		st->ret = 1;
	}
	else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] == ' ')
	{
		if (first[0] != '\0')
		{
			free((char *)st->tokens->content);
			st->tokens->content = ft_strjoin(first, trad[0]);
			a = 1;
		}
		if (after[0] != '\0' && trad[1] == NULL)
		{
			if (first[0] == '\0')
			{
				free((char *)st->tokens->content);
				st->tokens->content = ft_strdup(trad[0]);
			}
			a = 1;
			b = 0;
			while (trad[b])
				b++;
			fri = trad[b - 1];
			trad[b - 1] = ft_strjoin(trad[b - 1], after);
			free(fri);
			st->pass += ft_strlen(after);
		}
	}
	free(st->tmpq);
	st->tmpq = ft_strdup((char *)st->tokens->content);
	b = 0;
	while (trad[b])
		b++;
	while (a < b && trad[a])
	{
		ft_lstadd_back(&st->tokens, ft_lstnew(ft_strdup(trad[a])));
		st->ddone += 1;
		a++;
	}
	if (env[ft_strlen(env) - 1] == ' ' && after[0] != '\0')
		ft_lstadd_back(&st->tokens, ft_lstnew(ft_strdup(after)));
	ft_lstadd_back(&st->tokens, nex);
	ft_freetab(trad);
	free(backs);
	return (1);
}

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
		st->tmpq = ft_strdup(&ft_shlvl(&env[i], a)[6]);
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