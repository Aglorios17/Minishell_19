/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcap_history.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by gverhelp          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		get_history(t_termcap *tc)
{
	tc->line = ft_strdup("");
	if ((tc->history = get_tab()))
	{
		tc->i = 0;
		while (tc->history[tc->i])
			tc->i++;
		tc->y = tc->i;
	}
}

void		ft_write_in_history(t_termcap *tc)
{
	if (tc->line[0] != '\0')
	{
		write(tc->fdhist, tc->line, ft_strlen(tc->line));
		write(tc->fdhist, "\n", 1);
	}
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
