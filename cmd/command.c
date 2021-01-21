#include "../include/minishell.h"

int ft_command(shell *st, char **envp)
{
	char *tmp;
	int i;
//	int a;
//	printf("|%s|\n", (char *)st->tokens->content);

	tmp = NULL;
	i = 0;
//	a = 0;
	if (!st->tokens)
		return (0);
	if (!(ft_strncmp((char *)st->tokens->content, "exit", 5)))
		return (ft_exit(st));
	else if (!(ft_strncmp((char *)st->tokens->content, "echo", 5)))
	{
		ft_echo(st);
		st->status = 0;
//		if (st->errorredir == 1)
//			st->status = 1;
//		st->errorredir = 0;
	}
	else if (!ft_strncmp((char *)st->tokens->content, "pwd", 4))
	{
		write(1, ft_pwd(st), ft_strlen(ft_pwd(st)));
		write(1, "\n", 1);
	}
	else if (!ft_strncmp((char *)st->tokens->content, "cd", 3))
	{
		if (ft_cd(st) == 1)
		{
			st->pwd = ft_pwd(st);
			while (st->envv)
			{
				tmp = (char *)st->envv->content;
				if (!ft_strncmp(tmp, "PWD=", 4))
				{
					if (st->pwd)
					{
						i = 0;
						while (tmp[i] != '=')
							i++;
						if (tmp[i] == '=')
							i++;
					//	if (!ft_strcmp(st->pwd, st->oldpwd))
						st->envv->content = ft_strjoin("PWD=", st->pwd);
//					printf("envv||%s||\n", (char *)st->envv->content);
						break;
					}
				}
				st->envv = st->envv->next;
			}
			st->envv = st->firstenv;
		}
	}
	else if (!ft_strncmp((char *)st->tokens->content, "export", 7))
	{
	//	printf("|okexport|\n");
		ft_export(st, envp);
	}
	else if (!ft_strncmp((char *)st->tokens->content, "unset", 6))
	{
		st->tokens = st->tokens->next;
		while (st->tokens)
		{
			ft_unset(st);
			st->tokens = st->tokens->next;
		}
		st->tokens = st->firsttok;
	}
	else if (!ft_strncmp((char *)st->tokens->content, "env", 4))
	{
		while (st->envv)
		{
			if (!ft_strcmp((char *)st->envv->content, "_=env"))
				write(1, "_=/home/user42/Bureau/minishell_test/bin/env", 44);
			else
				write(1, (char *)st->envv->content, ft_strlen((char *)st->envv->content));
			write(1, "\n", 1);
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
	}
	else	
	{
	//	printf("|ok|\n");
		ft_exec(st);
	}
//	st->oldpwd = ft_pwd(st);
	return (0);
}

int	ft_checkcommand(shell *st)
{
	char *tmp;

	tmp = (char *)st->tokens->content;
//	printf("|ok|\n");
	if (check_path(st, tmp) == 1)
	{
		return (1);
	}
//	printf("|ok2|\n");
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "env") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}
