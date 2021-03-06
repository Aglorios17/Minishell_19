/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	cdhome(t_shell *st, char *line, char *tmp, char *env)
{
	int i;

	i = 0;
	while (st->envv)
	{
		env = (char *)st->envv->content;
		if (!ft_strncmp(env, "HOME=", 5))
		{
			i = 0;
			while (env[i] && env[i] != '=')
				i++;
			if (env[i] && env[i] == '=')
				i++;
			line = ft_strdup(&env[i]);
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (cdhomereturn(st, line, tmp));
}

int	cderror(t_shell *st, char *tmp)
{
	st->oldpwd = tmp;
	write(1, "minishell: ", 11);
	write(1, "cd: ", 4);
	write(1, "too many arguments\n", 19);
	st->status = 1;
	return (0);
}

int	cdwave(t_shell *st, char *env)
{
	int i;

	i = 0;
	while (st->envv)
	{
		env = (char *)st->envv->content;
		if (!ft_strncmp(env, "HOME=", 5))
		{
			i = 0;
			while (env[i] && env[i] != '=')
				i++;
			if (env[i] && env[i] == '=')
				i++;
			st->pwd = ft_strdup(&env[i]);
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (0);
}

int	docd(t_shell *st, char *line, char *tmp)
{
	if (chdir(st->pwd) < 0)
	{
		open_pathcd(st, (char *)st->tokens->next->content);
		st->oldpwd = tmp;
		if (line)
			free(line);
		st->status = 1;
		return (0);
	}
	if (line)
		free(line);
	oldpwd(st);
	return (1);
}

int	ft_cd(t_shell *st)
{
	char	*line;
	char	*tmp;
	char	*env;

	env = NULL;
	tmp = st->oldpwd;
	st->oldpwd = st->pwd;
	line = NULL;
	if (st->tokens->next && st->tokens->next->next)
		return (cderror(st, tmp));
	if (!st->tokens->next)
		return (cdhome(st, line, tmp, env));
	if (line)
		free(line);
	line = ft_strdup((char *)st->tokens->next->content);
	if (st->tokens->next && line[0] != '\0')
		st->pwd = ft_strdup(line);
	if (!ft_strncmp(st->pwd, "~\0", 2))
		cdwave(st, env);
	return (docd(st, line, tmp));
}
