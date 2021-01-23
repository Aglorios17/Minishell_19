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
	st->pipe = NULL;
	st->firstpipe = NULL;
	st->pat = NULL;
	st->fdout = 1;
	st->fdone = 1;
	st->pipefd = 0;
	st->errorredir = 0;
	st->rd = 0;
}

int	ft_pipe(shell *st)
{
	int		pop[2];
	pid_t	cpid;

	wait(NULL);
	if (!st->pipe->next)
		st->fdout = st->fdone;
	if (st->pipe->next)
	{
		if (pipe(pop) > 0)
			exit(1);
//		printf("ok1\n");
//		printf("pop[0]|%i|\n", pop[0]);
//		printf("pop[1]|%i|\n", pop[1]);
		if ((cpid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		}
		if (cpid == 0)
			close(pop[0]);
		else
			close(pop[1]);
//		printf("ok2\n");
//		printf("pop[0]|%i|\n", pop[0]);
//		printf("pop[1]|%i|\n", pop[1]);
		st->fdout = pop[1];
	}
	return (1);
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
		ft_cutpipe(st);
		st->fdone = dup(st->fdout);
		while (st->pipe)
		{
//			ft_pipe(st);
//			printf("st->fdone|%i|\n", st->fdone);
//			printf("st->fdout|%i|\n", st->fdout);
			if (ft_tokens(st) == 1)
			{
				if (st->status == 2)
				{
					free(st->home);
					ft_exfree2(st, tmp);
					return (1);
				}
				else
					st->status = 1;
			}
			else
			{
				if (st->tokens)
					ft_cleantokens(st);
				if (ft_command(st, envp) == 1)
				{
					free(st->home);
					ft_exfree2(st, tmp);
					return (1);
				}
			}
			if (st->fdout == 0)
			{
				close(st->fdout);
				st->fdout = dup2(st->fdone, 0);
			}
			else
			{
				close(st->fdout);
				st->fdout = dup2(st->fdone, 1);
			}
			st->pipe = st->pipe->next;	
			ft_exfree(st, tmp);
		}
		ft_freecutpipe(st, tmp);
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
			write(2,">>",2);
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
