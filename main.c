#include "minishell.h"

void ft_init_struct(shell *st)
{
	st->ret = 0;
	st->quotes = 0;
	st->line = NULL;
	st->pwd = NULL;
	st->home = NULL;
	st->firsttok = NULL;
	st->tmpq = NULL;
	st->tokens = NULL;
	st->home = ft_pwd(st);
}

int	ft_exfree(shell *st, t_list *tmp)
{
	free(st->line);
//	free(st->pwd);
	st->line = NULL;
	st->tokens = st->firsttok;
	st->firsttok = NULL;
	while (st->tokens != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->tokens->content);
		st->tokens->content = NULL;
		tmp = st->tokens;
		st->tokens = st->tokens->next;
		free(tmp);
		tmp = NULL;
	}
	st->tokens = NULL;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	shell	st;
	t_list	*tmp;

	ft_init_struct(&st);
	tmp = NULL;
//	write(1,"\n",1);
//	write(1,"by Aglorios and Gverhelp\n",25);
//	write(1,"\n",1);
	(void)argc;
	(void)argv;
//	st.home = "/Users/aglorios";
//	envp = 0;
	if  (argc > 1 && !ft_strncmp(argv[1], "-c", 2))
	{
		st.line = ft_strdup(argv[2]);
//		write(1,"1\n",2);
		if (ft_tokens(&st))
			return (0);
//		write(1,"1\n",2);
		if (st.tokens)
			ft_cleantokens(&st);
//		write(1,"2\n",2);
//		printf("%s", st.line);
		if (ft_command(&st, envp))
			return (0);
//		write(1,"3\n",2);
		if (st.ret == 1)
		{
//			write(1,"4\n",2);
			return (127);
		}
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
//			write(1,"1\n",2);
			ft_tokens(&st);
//			write(1,"2\n",2);
			if (st.tokens)
				ft_cleantokens(&st);
//			write(1,"3\n",2);
			if (ft_command(&st, envp))
			{
				free(st.home);
				return (ft_exfree(&st, tmp));
			}
//			write(1,"4\n",2);
			ft_exfree(&st, tmp);
	//		if (st.ret == 1)
	//			return (127);
		}
	}
	free(st.home);
	return (0);
}
