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
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler2);
	while (1)
	{
		free(st->line);
		if (sg->prompt == 0)
			write(2, ">>", 2);
		sg->prompt = 0;
		if (get_next_line3d(0, &st->line) != 1)
		{
			write(2, "exit\n", 5);
			return (0);
		}
		if (mainprocess(st) == 1)
			break ;
	}
	return (0);
}

t_sign	*initglobal(void)
{
	static t_sign	sg;

	return (&sg);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell	st;
	t_sign	*sg;

	ft_init_struct(&st);
	sg = initglobal();
	sg->pid = 1;
	sg->pid2 = 0;
	sg->prompt = 0;
	sg->nc = 0;
	ft_envv(&st, envp);
	if (argc > 1 && !ft_strncmp(argv[1], "-c", 2))
		test(&st, argv);
	else
		codeexec(&st);
	return (ft_free_end(&st));
}
