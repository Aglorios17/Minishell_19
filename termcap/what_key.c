/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by gverhelp          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_write_line(t_termcap *tc, char *str)
{
	char	*fri;
	char	*tmp;

	fri = NULL;
	tmp = NULL;
	if (tc->cursor == tc->dist)
	{
		fri = tc->line;
		tc->line = ft_strjoin(tc->line, str);
		free(fri);
	}
	else
	{
		tmp = ft_substr(tc->line, 0, tc->cursor);
		fri = ft_strjoin(str, &tc->line[tc->cursor + 1]);
		free(tc->line);
		tc->line = ft_strjoin(tmp, fri);
		free(fri);
		free(tmp);
		tc->dist--;
	}
	write(1, str, tc->len);
}

void	ft_backspace_inline(t_termcap *tc)
{
	char	*fri;
	char	*tmp;

	fri = NULL;
	tmp = NULL;
	tmp = ft_substr(tc->line, 0, tc->cursor - 1);
	fri = ft_strdup(&tc->line[tc->cursor]);
	free(tc->line);
	tc->line = ft_strjoin(tmp, fri);
	free(tmp);
	free(fri);
}

void	ft_key_backspace(t_termcap *tc)
{
	char	*fri;

	fri = NULL;
	if (tc->dist == 0 || tc->cursor == 0)
		return ;
	if (tc->dist == tc->cursor)
	{
		fri = ft_substr(tc->line, 0, ft_strlen(tc->line) - 1);
		free(tc->line);
		tc->line = ft_strdup(fri);
		free(fri);
	}
	else
		ft_backspace_inline(tc);
	tputs(cursor_left, 1, ft_putchar2);
	tputs(tgetstr("dc", NULL), 1, ft_putchar2);
	tc->cursor--;
	tc->dist--;
}

void	ft_key_down(t_termcap *tc)
{
	if (tc->i + 1 < tc->y)
	{
		tc->i++;
		tputs(tgetstr("dl", NULL), 1, ft_putchar2);
		tputs(">>", 1, ft_putchar2);
		tputs(tc->history[tc->i], 1, ft_putchar2);
		free(tc->line);
		tc->line = ft_strdup(tc->history[tc->i]);
		tc->dist = ft_strlen(tc->line);
		tc->cursor = tc->dist;
	}
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
		tc->dist = ft_strlen(tc->line);
		tc->cursor = tc->dist;
	}
	return (1);
}
