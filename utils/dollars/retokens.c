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

int	ft_flagdq(shell *st, char *backs, char *env, int a)
{
	free((char *)st->tokens->content);
	st->tokens->content = ft_strdup(&env[a + 1]);
	free(st->tmpq);
	st->tmpq = ft_strdup((char *)st->tokens->content);
	free(backs);
	return (1);
}

int	tradnull(shell *st, char **trad, int a, char *backs, char *after, char *first, char *env)
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
		st->tmpq = ft_strdup((char *)st->tokens->content);
	}
	ft_freetab(trad);
	free(backs);
	return (1);
}

int	readdtok(shell *st, char **trad, int a, char *backs, char *after, char *env, t_list *nex)
{
	int c;

	c = 0;
	while (trad[c])
		c++;
	while (a < c && trad[a])
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

int	retok2(int c, shell *st, char **trad, int a, char *backs, char *after, char *first)
{
	char	*fri;

	fri = NULL;
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
				a = 0;
				while (trad[a])
					a++;
				if (after[0] == '\\')
				{
					if (c == 1)
					{
						fri = trad[a - 1];
						trad[a - 1] = ft_strjoin(trad[a - 1], backs);
						free(fri);
					}
					else
					{
						fri = trad[a - 1];
						trad[a - 1] = ft_strjoin(trad[a - 1], " ");
						free(fri);
					}
				}
				else
				{
					fri = trad[a - 1];
					trad[a - 1] = ft_strjoin(trad[a - 1], after);
					free(fri);
				}
				a = 1;
				st->pass += ft_strlen(after);
			}
		}
	}
	return (a);
}

int	spaceafter(shell *st, char **trad, int a, char *first, char *after, char *env)
{
	char	*fri;

	fri = NULL;
	if (first[0] != '\0')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(first);
		if (after[0] != '\0' && env[ft_strlen(env) - 1] != ' ')
		{
			a = 0;
			while (trad[a])
				a++;
			fri = trad[a - 1];
			trad[a - 1] = ft_strjoin(trad[a - 1], after);
			free(fri);
		}
		a = 0;
	}
	else
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(trad[0]);
		a = 1;
	}
	st->ret = 1;
	return (a);
}

int		retokspaceafter(shell *st, char **trad, int a, char *after, char *first)
{
	char	*fri;

	fri = NULL;
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
		a = 0;
		while (trad[a])
			a++;
		fri = trad[a - 1];
		trad[a - 1] = ft_strjoin(trad[a - 1], after);
		free(fri);
		st->pass += ft_strlen(after);
		a = 1;
	}
	return (a);
}

int	switchretok(int c, shell *st, char **trad, int a, char *backs, char *after, char *first, char *env)
{
	if (first[0] == '\0' && after[0] == '\0' &&
		env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(trad[0]);
		a = 1;
	}
	else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
		a = retok2(c, st, trad, a, backs, after, first);
	else if (first[0] == '\0' && after[0] == '\0' &&
		env[a + 1] == ' ' && env[ft_strlen(env) - 1] == ' ')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(trad[0]);
		a = 1;
	}
	else if (env[a + 1] == ' ')
		a = spaceafter(st, trad, a, first, after, env);
	else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] == ' ')
		a = retokspaceafter(st, trad, a, after, first);
	return (a);
}

int		ft_retokens(shell *st, char *env, char *first, char *after)
{
	int		a;
	int		c;
	char	**trad;
	char	*backs;
	char	*fri;
	t_list	*nex;

	a = 0;
	c = 0;
	trad = NULL;
	if (st->tmpq)
		free(st->tmpq);
	st->tmpq = ft_strdup("");
	backs = ft_strdup("");
	nex = NULL;
	fri = NULL;
	while (after[c] && ft_strchr(after, '\\'))
	{
		if (after[c] == '\\' && (after[c + 1] == ' ' || after[c + 1] == '\0'))
		{
			fri = backs;
			backs = ft_charjoin(backs, ' ');
			free(fri);
			c += 2;
		}
		else
		{
			if (after[c] == '\\' && after[c + 1] == '\\')
				c++;
			fri = backs;
			backs = ft_charjoin(backs, after[c]);
			free(fri);
			c++;
		}
	}
	if (c != 0 && after[2] != '\0')
		c = 1;
	else
		c = 0;
	st->ddone = 0;
	while (env[a] && env[a] != '=')
		a++;
	if (st->flagdq == 0 && env[a])
		trad = ft_split(&env[a + 1], ' ');
	else if (st->flagdq == 1)
		return (ft_flagdq(st, backs, env, a));
	if (trad[0] == NULL)
		return (tradnull(st, trad, a, backs, after, first, env));
	if (st->tokens->next)
	{
		nex = st->tokens->next;
		st->tokens->next = NULL;
	}
	a = switchretok(c, st, trad, a, backs, after, first, env);
	free(st->tmpq);
	st->tmpq = ft_strdup((char *)st->tokens->content);
	c = 0;
	return (readdtok(st, trad, a, backs, after, env, nex));
}
