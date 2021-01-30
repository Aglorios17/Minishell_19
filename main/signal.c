/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signalhandler(int signum)
{
	(void)signum;
	if (pid == 0)
	{
		kill(0, 0);
		pid = 1;
		pid2 = 0;
	}
	else
	{
		if (nc == 0)
			write(2, "\n>>", 3);
		else
			write(2, "\n", 1);
		nc = 0;
		prompt = 1;
	}
}

void	signalhandler2(int signum)
{
	(void)signum;
	if (pid2 > 0)
	{
		kill(0, 0);
		write(2, "\nCORE DUMP CONNARD", 18);
		if (nc == 0)
			write(2, "\n>>", 3);
		else
			write(2, "\n", 1);
		prompt = 1;
		pid2 = 0;
	}
	else
	{
		if (nc == 0)
			write(2, "\n>>", 3);
		else
			write(2, "\n", 1);
		nc = 0;
		prompt = 1;
	}
}
