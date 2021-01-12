#include "minishell.h"

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
}

int	ft_exfree2(shell *st, t_list *tmp)
{
	if (st->tmpq)
	{
		free(st->tmpq);
		st->tmpq = NULL;
	}
	if (st->line)
	{
		free(st->line);
		st->line = NULL;
	}
//	free(st->pwd);
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
	st->envv = st->firstenv;
	st->firstenv = NULL;
	while (st->envv != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->envv->content);
		st->envv->content = NULL;
		tmp = st->envv;
		st->envv = st->envv->next;
		free(tmp);
		tmp = NULL;
	}
	st->envv = NULL;
	if (st->status != 0)
		return (st->status);
	return (0);
}

int	ft_exfree(shell *st, t_list *tmp)
{
	if (st->tmpq)
	{
		free(st->tmpq);
		st->tmpq = NULL;
	}
	if (st->line)
	{
		free(st->line);
		st->line = NULL;
	}
//	free(st->pwd);
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
/*	st->envv = st->firstenv;
	st->firstenv = NULL;
	while (st->envv != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->envv->content);
		st->envv->content = NULL;
		tmp = st->envv;
		st->envv = st->envv->next;
		free(tmp);
		tmp = NULL;
	}
	st->envv = NULL;
*/	if (st->status != 0)
		return (st->status);	
	return (0);
}

int	ft_freecutline(shell *st, t_list *tmp)
{
	st->cutline = st->firstcut;
	st->firstcut = NULL;
	while (st->cutline != NULL)
	{
//		printf("|%s|", (char *)st->tokens->content);
		free(st->cutline->content);
		st->cutline->content = NULL;
		tmp = st->cutline;
		st->cutline = st->cutline->next;
		free(tmp);
		tmp = NULL;
	}
	st->cutline = NULL;
	return (0);
}

int lstcmd(shell *st, char *line)
{
	int i;
	int a;
	char *tmp;

	i = 0;
	a = 0;
	tmp = NULL;
	while (st->envv)
	{
		tmp = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(tmp, "=", 1))
			a = 1;
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 1)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	tmp = ft_strdup("");
	while (line[i] && line[i] != ' ')
	{
		tmp = ft_charjoin(tmp, line[i]);
		i++;
	}
//	tmp = ft_strdup("/home/user42/Bureau/minishell_test/bin/env");
//	printf("|%s|\n",tmp);
	a = 0;
	while (st->envv)
	{
		if (!ft_strcmp((char *)st->envv->content, ft_strjoin("_=", tmp)))
			a = 1;
		else if (!ft_strncmp((char *)st->envv->content, "_=", 2))
		{
			st->envv->content = ft_strjoin("_=", tmp);
			a = 1;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("_=", tmp)));
	st->envv = st->firstenv;
	return (1);
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
	ft_envv(&st, envp);
	if  (argc > 1 && !ft_strncmp(argv[1], "-c", 2))
	{
		st.line = ft_strdup(argv[2]);
//		writdde(1,"1\n",2);
		lstcmd(&st, st.line);
		ft_cutline(&st);
//		st.status = 0; /////////////////////// hereeeee 
		while (st.cutline)
		{
//			if (st.status != 2)
//				st.status = 0; /////////////////////// hereeeee 
			ft_tokens(&st);
			if (st.tokens)
				ft_cleantokens(&st);
//			write(1,"2\n",2);
			if (ft_command(&st, envp) == 1)
			{
				free(st.home);
	//			printf("status|%i|", st.status);
				return (ft_exfree2(&st, tmp));
			}
//			write(1,"3\n",2);
			if (st.cutline->next)
				st.status = 0;
			ft_exfree(&st, tmp);
			st.cutline = st.cutline->next;
		}
		ft_freecutline(&st, tmp);
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
			lstcmd(&st, st.line);
			ft_cutline(&st);
//			write(1,"1\n",2);
			while (st.cutline)
			{
				if (st.status != 2)
					st.status = 0; /////////////////////// hereeeee 
	//			write(1,"1\n",2);
				ft_tokens(&st);
	//			write(1,"2\n",2);
				if (st.tokens)
					ft_cleantokens(&st);
//				write(1,"3\n",2);
				if (ft_command(&st, envp) == 1)
				{
					free(st.home);
					return (ft_exfree2(&st, tmp));
				}
//				write(1,"4\n",2);
				ft_exfree(&st, tmp);
				st.cutline = st.cutline->next;
			}
			ft_freecutline(&st, tmp);
		}
	}
	free(st.home);
	if (st.status != 0)
		return (st.status);
	return (0);
}
