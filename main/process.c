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

int		commandline(t_shell *st)
{
	if (ft_tokens(st) == 1)
		st->status = 1;
	else
	{
		if (st->tokens)
			ft_cleantokens(st);
		if (ft_command(st) == 1)
			return (1);
	}
	close(st->fdout);
	if (st->fdout == 0)
		st->fdout = dup2(st->fdone, 0);
	else
		st->fdout = dup2(st->fdone, 1);
	return (0);
}

int		mainprocess(t_shell *st)
{
	ft_cutline(st);
	while (st->cutline)
	{
		ft_cutpipe(st);
		st->fdone = dup(st->fdout);
		while (st->pipe)
		{
			if (ft_pipe(st) == 1)
				return (1);
			ft_free_command(st);
			st->pipe = st->pipe->next;
		}
		ft_free_list(st->pipe, st->firstpipe);
		st->cutline = st->cutline->next;
	}
	if (st->status != 2)
		ft_free_list(st->cutline, st->firstcut);
	free(st->line);
	return (0);
}
