/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by gverhelp          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_newline_history(t_termcap *tc, char **add)
{
	char **fri;

	fri = NULL;
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
		fri = tc->history;
		tc->history = ft_tabjoin(tc->history, add);
		ft_freetab(fri);
		ft_freetab(add);
		tc->y++;
		tc->a = 1;
	}
	if (tc->i + 1 == tc->y && tc->a == 1)
	{
		free(tc->history[tc->i]);
		tc->history[tc->i] = ft_strdup(tc->line);
	}
	return (1);
}

int		ft_key_up(t_termcap *tc, char **add)
{
	if (!ft_newline_history(tc, add))
		return (0);
	if (tc->i != 0)
	{
		tc->i--;
		tputs(tgetstr("dl", NULL), 1, ft_putchar2);
		tputs(">>", 1, ft_putchar2);
		tputs(tc->history[tc->i], 1, ft_putchar2);
		free(tc->line);
		tc->line = ft_strdup(tc->history[tc->i]);
	}
	return (1);
}

int		ft_loop(t_termcap *tc, char **add, char *str)
{
	str[tc->len] = 0;
	if (!ft_strcmp(str, "\4"))
		return (-1);
	if (!ft_strcmp(str, "\e[A"))
	{
		if (!ft_key_up(tc, add))
			return (-1);
	}
	else if (!ft_strcmp(str, "\e[B"))
		ft_key_down(tc);
	else if (!ft_strcmp(str, "\n"))
	{
		write(1, "\n", 1);
		tc->a = 0;
		return (1);
	}
	else if (!ft_strcmp(str, key_backspace))
		ft_key_backspace(tc);
	else // (ft_strcmp(str, "\e[D") && ft_strcmp(str, "\e[C"))
		ft_write_line(tc, str);
	return (0);
}

char	*return_termcap(t_termcap *tc, int i)
{
	ft_write_in_history(tc);
	ft_freetab(tc->history);
	close(tc->fdhist);
	if (i == -1)
	{
		free(tc->line);
		return (NULL);
	}
	return (tc->line);
}

char	*ft_termcap(void)
{
	char		str[2000];
	char		**add;
	int			i;
	t_termcap	tc;

	add = NULL;
	init_struct_tc(&tc);
	if (!init_term())
		return (NULL);
	i = 0;
	if ((tc.fdhist = open(".minishell_history", O_WRONLY |
		O_APPEND | O_CREAT, 0644)) < 0)
		return (NULL);
	get_history(&tc);
	while (((tc.len = read(0, str, 100)) != 0))
	{
		i = ft_loop(&tc, add, str);
		if (i == -1)
			break ;
		else if (i == 1)
			break ;
	}
	return (return_termcap(&tc, i));
}
