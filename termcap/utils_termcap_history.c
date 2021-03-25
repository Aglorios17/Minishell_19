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

void	get_history(t_termcap *tc)
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

void	ft_write_in_history(t_termcap *tc)
{
	if (tc->line[0] != '\0')
	{
		write(tc->fdhist, tc->line, ft_strlen(tc->line));
		write(tc->fdhist, "\n", 1);
	}
}
