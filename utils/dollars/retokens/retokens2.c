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

#include "../../../include/minishell.h"

char	*retokjoin(t_dol *dol, char **trad, int a)
{
	char *fri;

	fri = NULL;
	if (dol->after[0] == '\\')
		trad[a - 1] = retok2cafter(dol, trad, a);
	else
	{
		fri = trad[a - 1];
		trad[a - 1] = ft_strjoin(trad[a - 1], dol->after);
		free(fri);
	}
	return (trad[a - 1]);
}

int		retok2(t_shell *st, t_dol *dol, char **trad, int a)
{
	a = retok2first(st, dol, trad, a);
	if (dol->after[0] != '\0')
	{
		if (trad[1] == NULL)
			retok2tradunnull(st, dol, trad);
		else
		{
			retok2tok(st, dol, trad);
			if (dol->after[0] != '\0')
			{
				a = 0;
				while (trad[a])
					a++;
				trad[a - 1] = retokjoin(dol, trad, a);
				a = 1;
				st->pass += ft_strlen(dol->after);
			}
		}
	}
	return (a);
}

int		spaceafter(t_shell *st, t_dol *dol, char **trad, int a)
{
	char	*fri;

	if (dol->first[0] != '\0')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(dol->first);
		if (dol->after[0] != '\0' && dol->env[ft_strlen(dol->env) - 1] != ' ')
		{
			a = 0;
			while (trad[a])
				a++;
			fri = trad[a - 1];
			trad[a - 1] = ft_strjoin(trad[a - 1], dol->after);
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

int		retokspaceafter(t_shell *st, t_dol *dol, char **trad, int a)
{
	char	*fri;

	if (dol->first[0] != '\0')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strjoin(dol->first, trad[0]);
		a = 1;
	}
	if (dol->after[0] != '\0' && trad[1] == NULL)
	{
		if (dol->first[0] == '\0')
		{
			free((char *)st->tokens->content);
			st->tokens->content = ft_strdup(trad[0]);
		}
		a = 0;
		while (trad[a])
			a++;
		fri = trad[a - 1];
		trad[a - 1] = ft_strjoin(trad[a - 1], dol->after);
		free(fri);
		st->pass += ft_strlen(dol->after);
		a = 1;
	}
	return (a);
}

int		switchretok(t_shell *st, t_dol *dol, char **trad, int a)
{
	if (dol->first[0] == '\0' && dol->after[0] == '\0' &&
		dol->env[a + 1] != ' ' && dol->env[ft_strlen(dol->env) - 1] != ' ')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(trad[0]);
		a = 1;
	}
	else if (dol->env[a + 1] != ' ' && dol->env[ft_strlen(dol->env) - 1] != ' ')
		a = retok2(st, dol, trad, a);
	else if (dol->first[0] == '\0' && dol->after[0] == '\0' &&
		dol->env[a + 1] == ' ' && dol->env[ft_strlen(dol->env) - 1] == ' ')
	{
		free((char *)st->tokens->content);
		st->tokens->content = ft_strdup(trad[0]);
		a = 1;
	}
	else if (dol->env[a + 1] == ' ')
		a = spaceafter(st, dol, trad, a);
	else if (dol->env[a + 1] != ' ' && dol->env[ft_strlen(dol->env) - 1] == ' ')
		a = retokspaceafter(st, dol, trad, a);
	return (a);
}
