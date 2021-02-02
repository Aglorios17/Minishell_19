/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		dopipe(shell *st)
{
	int		pop[2];
	pid_t	cpid;

	if (pipe(pop) > 0)
		exit(1);
	if ((cpid = fork()) == -1)
		exit(1);
	if (cpid == 0)
	{
		pid = cpid;
		close(pop[0]);
		st->fdout = dup2(pop[1], 1);
		if (commandline(st) == 1)
			return (1);
		exit(0);
	}
	else if (cpid > 0)
	{
		close(pop[1]);
		st->fdout = dup2(pop[0], 0);
		wait(NULL);
	}
	return (0);
}

int		ft_pipe(shell *st)
{
	if (!st->pipe->next)
	{
		if (commandline(st) == 1)
			return (1);
		return (0);
	}
	if (st->pipe->next)
		dopipe(st);
	return (0);
}
