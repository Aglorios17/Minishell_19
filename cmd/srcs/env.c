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

#include "../../include/minishell.h"

int		ft_envv(shell *st, char **envp)
{
	int a;
	int i;
	int p;
	int e;
	int s;
	char *tmp;
	int num;
	char *fri;
	
	a = 0;
	p = 0;
	e = 0;
	s = 0;
	tmp = NULL;
	num = 0;
	i = 0;
	fri = NULL;
	while (envp[a])
	{
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(envp[a])));                              ///// free strdup
		a++;
	}
	st->firstenv = st->envv;
	st->envv = st->firstenv;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "PWD", 3))
			p = 1;
		if (!ft_strncmp(tmp, "_", 1))
			e = 1;
		if (!ft_strncmp(tmp, "SHLVL", 5))
		{
			i = 0;
			while (tmp[i] && tmp[i] != '=')
				i++;
			if (tmp[i] && tmp[i] == '=')
				i++;
			num = ft_atoi2(&tmp[i]) + 1;
			st->envv->content = ft_strjoin("SHLVL=", fri = ft_itoa(num));   
			/// free join;
			free(fri);
			s = 1;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (p == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("PWD=", ft_pwd(st))));                     //// free join
	if (s == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup("SHLVL=1")));                               //// free join
	if (e == 0)   
		(void)st;
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
	line = ft_strjoin("SHLVL=", line);                                               //// free line
	return (line);
}
