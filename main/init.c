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

void	ft_init_struct2(shell *st)
{
	st->status = 0;
	st->cutline = 0;
	st->pipe = NULL;
	st->firstpipe = NULL;
	st->pat = NULL;
	st->fdout = 1;
	st->fdone = 1;
	st->pipefd = 0;
	st->fdredir = 0;
	st->rd = 0;
	st->new = NULL;
	st->cmdexec = NULL;
	st->itrad = 0;
	st->line = NULL;
}

void	ft_init_struct(shell *st)
{
	st->ret = 0;
	st->quotes = 0;
	st->quotes2 = 0;
	st->line = NULL;
	st->pwd = NULL;
	st->pwdcp = NULL;
	st->oldpwd = NULL;
	st->firsttok = NULL;
	st->tmpq = NULL;
	st->tokens = NULL;
	st->envv = NULL;
	st->firstenv = NULL;
	st->flagdq = 0;
	ft_init_struct2(st);
}
