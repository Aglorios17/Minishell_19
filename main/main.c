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
}

int		commandline(shell *st)
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

int		ft_pipe(shell *st)
{
	int		pop[2];
	pid_t	cpid;

	if (!st->pipe->next)
	{
		if (commandline(st) == 1)
			return (1);
		return (0);
	}
	if (st->pipe->next)
	{
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
	}
	return (0);
}

int		mainprocess(shell *st)
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
	ft_free_list(st->cutline, st->firstcut);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	shell	st;

	ft_init_struct(&st);
	pid = 1;
	pid2 = 0;
	prompt = 0;
	nc = 0;
	ft_envv(&st, envp);
	if (argc > 1 && !ft_strncmp(argv[1], "-c", 2))
	{
		st.line = ft_strdup(argv[2]);
		lstcmd(&st, st.line);
		mainprocess(&st);
	}
	else
	{
		signal(SIGINT, signalhandler);
		signal(SIGQUIT, signalhandler2);
		while (1)
		{
			free(st.line);
			if (prompt == 0)
				write(2, ">>", 2);
			prompt = 0;
			if (get_next_line3d(0, &st.line) != 1)
			{
				ft_free_end(&st);
				write(1, "exit\n", 5);
				return (0);
			}
			if (mainprocess(&st) == 1)
				break ;
		}
	}
	return (ft_free_end(&st));
}
