/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/09 14:52:21 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		test(t_shell *st, char **argv)
{
	if (argv[2] && !argv[3])
	{
		st->line = ft_strdup(argv[2]);
		lstcmd(st, st->line);
		mainprocess(st);
	}
	return (0);
}

int		codeexec(t_shell *st)
{
	t_sign	*sg;

	sg = initglobal();
	(void)sg;
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler2);
	while (1)
	{
		write(2, ">>", 2);
		if (((st->line = ft_termcap(st)) == NULL))
		{
			write(2, "\nexit\n", 6);
			return (0);
		}
		if (mainprocess(st) == 1)
			break ;
		if (st->line)
		{
			free(st->line);
			st->line = NULL;
		}
	}
	return (0);
}

t_sign	*initglobal(void)
{
	static t_sign	sg;

	return (&sg);
}

t_shell	*globalstruct(void)
{
	static t_shell	st;

	return (&st);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell		*st;
	t_sign		*sg;

	st = globalstruct();
	ft_init_struct(st);
	sg = initglobal();
	sg->pid = 1;
	sg->pid2 = 0;
	sg->prompt = -1;
	sg->nc = 0;
	ft_envv(st, envp);
	if (argc > 1 && !ft_strncmp(argv[1], "-c", 2))
		test(st, argv);
	else
		codeexec(st);
	return (ft_free_end(st));
}
