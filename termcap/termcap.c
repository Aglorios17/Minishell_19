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

void	tab_or_other(t_termcap *tc, char *str)
{
	int i;

	i = 0;
	if (!ft_strcmp(str, "\t"))
	{
		(void)i;
		return ;
		i = 6;
		while (i-- != 0)
			ft_write_line(tc, " ");
		tc->cursor += 6;
		tc->dist += 6;
	}
	else
	{
		ft_write_line(tc, str);
		tc->cursor++;
		tc->dist++;
	}
}

int		print_else(t_termcap *tc, char *str)
{
	if (!ft_strcmp(str, "\e[C"))
	{
		if (tc->cursor == tc->dist)
			return (0);
		tputs(cursor_right, 1, ft_putchar2);
		tc->cursor++;
	}
	else if (!ft_strcmp(str, "\e[D"))
	{
		if (tc->cursor < 1)
			return (0);
		tc->cursor--;
		tputs(cursor_left, 1, ft_putchar2);
	}
	else if ((!ft_strcmp(str, "\e[D") ||
				!ft_strcmp(str, "\e[C")) && tc->dist == 0)
		return (0);
	else
		tab_or_other(tc, str);
	return (0);
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
		default_term();
		return (1);
	}
	else if (!ft_strcmp(str, key_backspace))
		ft_key_backspace(tc);
	else
		print_else(tc, str);
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
		tc->line = NULL;
		return (NULL);
	}
	return (tc->line);
}

char	*ft_termcap(t_shell *st)
{
	char		str[2000];
	char		**add;
	int			i;
	t_termcap	*tc;

	(void)st;
	add = NULL;
	tc = initglobalterm();
	init_struct_tc(tc);
	if (!init_term())
		return (NULL);
	i = 0;
	if ((tc->fdhist = open("/home/user42/.minishell_history",
		O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
		return (NULL);
	get_history(tc);
	while (((tc->len = read(0, str, 100)) > 0))
	{
		i = ft_loop(tc, add, str);
		if (i == -1)
			break ;
		else if (i == 1)
			break ;
	}
	return (return_termcap(tc, i));
}
