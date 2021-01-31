/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int		ft_checklevel(shell *st, char *tmp, int num)
{
	int		i;
	char	*fri;

	i = 0;
	fri = NULL;
	while (tmp[i] && tmp[i] != '=')
		i++;
	if (tmp[i] && tmp[i] == '=')
		i++;
	num = ft_atoi2(&tmp[i]) + 1;
	fri = ft_itoa(num);
	free((char *)st->envv->content);
	st->envv->content = ft_strjoin("SHLVL=", fri);
	free(fri);
	return (1);
}

int		ft_checkenv(shell *st, char *tmp, int num, int s)
{
	int		p;

	p = 0;
	st->envv = st->firstenv;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "PWD", 3))
			p = 1;
		if (!ft_strncmp(tmp, "SHLVL", 5))
			s = ft_checklevel(st, tmp, num);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (p == 0)
	{
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("PWD=", ft_pwd(st))));
	}
	return (s);
}

int		ft_getenv(shell *st, char **envp)
{
	int a;

	a = 0;
	while (envp[a])
	{
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(envp[a])));
		a++;
	}
	st->firstenv = st->envv;
	return (0);
}

int		ft_envv(shell *st, char **envp)
{
	int		s;
	char	*tmp;
	int		num;

	s = 0;
	tmp = NULL;
	num = 0;
	ft_getenv(st, envp);
	s = ft_checkenv(st, tmp, num, s);
	if (s == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup("SHLVL=1")));
	st->envv = st->firstenv;
	return (0);
}

char	*ft_shlvl(char *line, int i)
{
	int a;

	a = 0;
	a = ft_atoi(line);
	(void)i;
	if (a < 0)
		a = 0;
	if (a >= 1000)
	{
		write(1, "minishell: warning: shell level (", 33);
		write(1, ft_itoa(a), ft_strlen(ft_itoa(a)));
		write(1, ") too high, resetting to 1\n", 27);
		a = 1;
	}
	line = ft_itoa(a);
	line = ft_strjoin("SHLVL=", line);
	return (line);
}
