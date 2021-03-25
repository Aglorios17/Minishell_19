/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by gverhelp          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_termcap	*initglobalterm(void)
{
	static t_termcap tc;

	return (&tc);
}

char		*get_env_term(void)
{
	int			i;
	t_shell		*st;
	char		*env;
	char		*ret;

	st = globalstruct();
	env = NULL;
	ret = NULL;
	while (st->envv)
	{
		env = (char *)st->envv->content;
		if (!ft_strncmp(env, "TERM=", 5))
		{
			i = 0;
			while (env[i] && env[i] != '=')
				i++;
			if (env[i] && env[i] == '=')
				i++;
			ret = ft_strdup(&env[i]);
			break ;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	return (ret);
}

void		default_term(void)
{
	t_termios		term;

	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
}

void		add_line(t_termcap *tc, char **add)
{
	char **fri;

	fri = tc->history;
	tc->history = ft_tabjoin(tc->history, add);
	ft_freetab(fri);
	ft_freetab(add);
	tc->y++;
	tc->a = 1;
}

int			ft_newline_history(t_termcap *tc, char **add)
{
	if (tc->a == 0)
	{
		if (tc->line[0] == '\0')
		{
			if (!(add = malloc(sizeof(char*) * 2)))
				return (0);
			add[0] = ft_strdup("");
			add[1] = NULL;
		}
		else
		{
			add = ft_split(tc->line, '\n');
		}
		add_line(tc, add);
	}
	if (tc->i + 1 == tc->y && tc->a == 1)
	{
		free(tc->history[tc->i]);
		tc->history[tc->i] = ft_strdup(tc->line);
	}
	return (1);
}
