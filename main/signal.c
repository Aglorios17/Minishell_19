/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/09 14:51:31 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signalhandler(int signum)
{
	t_sign		*sg;
	t_shell		*st;
	t_termcap	*tc;

	sg = initglobal();
	st = globalstruct();
	tc = initglobalterm();
	sg->prompt = signum;
	if (!st->line && sg->pid2 == 0)
		write(2, "^C\n>>", 5);
	else
	{
		write(2, "\n", 1);
		kill(0, 0);
	}
	if (sg->pid2 == 0)
	{
		free(tc->line);
		tc->line = ft_strdup("");
	}
}

void	ft_promtsign(t_sign *sg)
{
	if (sg->nc == 0)
		write(2, "\n>>", 3);
	else
		write(2, "\n", 1);
	sg->nc = 0;
	sg->prompt = 1;
}

void	signalhandler2(int signum)
{
	t_sign		*sg;
	t_termcap	*tc;
	char		*fri;

	sg = initglobal();
	tc = initglobalterm();
	fri = NULL;
	sg->prompt = signum;
	if (sg->pid2 > 0)
	{
		kill(0, 0);
		fri = ft_itoa(sg->pid2);
		write(2, "\n[1]    ", 8);
		write(2, fri, ft_strlen(fri));
		write(2, " quit (core dumped)\n", 20);
		free(fri);
	}
	else
		write(2, "^\\\n>>", 5);
	if (sg->pid2 == 0)
	{
		free(tc->line);
		tc->line = ft_strdup("");
	}
	sg->pid2 = 0;
}
