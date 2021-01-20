#include "../include/minishell.h"

void ft_init_struct(shell *st)
{
	st->ret = 0;
	st->quotes = 0;
	st->quotes2 = 0;
	st->line = NULL;
	st->pwd = NULL;
	st->pwdcp = NULL;
	st->oldpwd = NULL;
	st->home = NULL;
	st->firsttok = NULL;
	st->tmpq = NULL;
	st->tokens = NULL;
	st->envv = NULL;
	st->firstenv = NULL;
	st->flagdq = 0;
	st->home = ft_pwd(st);
	st->status = 0;
	st->cutline = 0;
	st->pat = NULL;
}

int mainprocess(int argc, char **argv, char **envp, shell *st)
{
	t_list *tmp;

	tmp = NULL;
	(void)argc;
	(void)argv;
	lstcmd(st, st->line);
	ft_cutline(st);
	while (st->cutline)
	{
//		if (st.status != 2)
//			st.status = 0; /////////////////////// hereeeee 
//		write(1,"1\n",2);
		ft_tokens(st);
		if (st->tokens)
			ft_cleantokens(st);
//		write(1,"2\n",2);
		if (ft_command(st, envp) == 1)
		{
			free(st->home);
//			printf("status|%i|", st.status);
			ft_exfree2(st, tmp);
			return (1);
		}
//		write(1,"3\n",2);
//		if (st.cutline->next)
//			st.status = 0;
		ft_exfree(st, tmp);
//		statusenv(&st ,st.status);
		st->cutline = st->cutline->next;
	}
	ft_freecutline(st, tmp);
	return (0);
}
int main(int argc, char **argv, char **envp)
{
	shell	st;

	ft_init_struct(&st);
//	write(1,"\n",1);
//	write(1,"by Aglorios and Gverhelp\n",25);
//	write(1,"\n",1);
	(void)argc;
	(void)argv;
//	st.home = "/Users/aglorios";
//	envp = 0;
	ft_envv(&st, envp);
	if  (argc > 1 && !ft_strncmp(argv[1], "-c", 2))
	{
		st.line = ft_strdup(argv[2]);
		mainprocess(argc, argv, envp, &st);
	}
	else
	{
		while(1)
		{
			write(1,">>",2);
			if (get_next_line3d(0, &st.line) != 1)
			{
				write(1, "exit\n", 5);
				return(0);
			}
			if (mainprocess(argc, argv, envp, &st) == 1)
				break;
		}
	}
	free(st.home);
	if (st.status != 0)
		return (st.status);
	return (0);
}
