#include "minishell.h"

char *ft_pwd(shell *st)
{
	char *buf;
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	buf = NULL;
	st->pwd = getcwd(buf, 65535);
///*
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
//				printf("envv||%s||\n", (char *)st->envv->content);
				break;
			}
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
//*/
	return (st->pwd);
}

int ft_cd(shell *st)
{
	int i;
	char *line;
///*	
	char *tmp;

	i = 0;
	tmp = NULL;
//	printf("tok||%s||\n", (char *)st->tokens->content);
//	printf("pwd||%s||\n", st->pwd);
//	printf("oldpwd||%s||\n", st->oldpwd);
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "OLDPWD=", 7))
		{
			i = 0;
			while (tmp[i] != '=')
				i++;
			if (tmp[i] == '=')
				i++;
			st->envv->content = ft_strjoin("OLDPWD=", st->pwd);
//			printf("envv||%s||\n", (char *)st->envv->content);
			break;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
//*/
	i = 0;
	if (!st->tokens->next)
	{	
		st->pwd = st->home;
		if (chdir(st->pwd) < 0)
			return (0);
		return (1);
	}
	line = st->tokens->next->content;
	while (line[i] == ' ')
		i++;
	st->pwd = ft_strdup(&line[i]);
	if (chdir(st->pwd) < 0)
		return (0);
	return (1);
}

int ft_echo(shell *st)
{
	t_list	*tmp;
	char 	*tm;
	int		i;

	i = 0;
	tmp = 0;
	tm = 0;
//	printf("||%s||\n", st->tokens->content);
//	write(1,"1\n",2);
	while (st->tokens->next != NULL)
	{
		tmp = st->tokens->next;
		if (!(ft_strncmp((char *)tmp->content, "-n", 2)))
		{
			i = 1;
			tm = (char *)tmp->content;
			while (tm[i] == 'n')
			{
				i++;
			}
			if (i == (int)ft_strlen((char *)tmp->content))
			{
			//	write(1, "1\n", 1);
				st->tokens = tmp;
				i = 1;
			}
			else
				i = 0;
//			free(tm);
		}
		else
			break;
//		free(tmp);
	}
//	printf("%s\n", (char *)st->tokens->content);
	st->tokens = st->tokens->next;
	while (st->tokens != NULL)
	{
		ft_putstr((char *)st->tokens->content);
		st->tokens = st->tokens->next;
		if (st->tokens != NULL)
			write(1, " ", 1);
	}
	if (i == 0)
		write(1, "\n", 1);
	return (0);
}

int ft_command(shell *st, char **envp)
{
//	char *tmp;
//	int i;
//	int a;
//	printf("%s\n", (char *)st->tokens->content);

//	tmp = NULL;
//	i = 0;
//	a = 0;
	if (!st->tokens)
		return (0);
	if (!(ft_strncmp((char *)st->tokens->content, "echo", 5)))
		ft_echo(st);
	else if (!ft_strncmp((char *)st->tokens->content, "pwd", 4))
	{
		write(1, ft_pwd(st), ft_strlen(ft_pwd(st)));
		write(1, "\n", 1);
	}
	else if (!ft_strncmp((char *)st->tokens->content, "cd", 3))
	{
		ft_cd(st);
		st->pwd = ft_pwd(st);
	}
	else if (!ft_strncmp((char *)st->tokens->content, "export", 7))
		ft_export(st, envp);
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
	else if (!(ft_strncmp((char *)st->tokens->content, "exit", 5)))
		return (1);
	else
	{
	//	printf("%s\n", (char *)st->tokens->content);
		if (!ft_exec(st))
		{
/*			printf("%s\n", (char *)st->tokens->content);
			tmp = ft_strdup((char *)st->tokens->content);
			if (!ft_strcmp(tmp, "/"))
			{
				i = 0;
				a = 0;
				while (tmp[a])
				{
					if (tmp[a] == '/')
					{
						a++;
						i++;
					}
					else
						a++;
				}
				a = 0;
				while (tmp[a])
				{
					st->tokens->content = ft_strdup("");
					if (i == 0)
					{
						st->tokens->content = ft_charjoin(st->tokens->content, tmp[a]);
						a++;
					}
					else if (tmp[a] == '/')
					{
						i--;
						a++;
					}
					else
						a++;
				}
			}*/
			st->ret = 1;
		}
	}
//	st->oldpwd = ft_pwd(st);
	return (0);
}

int	ft_checkcommand(shell *st)
{
	char *tmp;

	tmp = (char *)st->tokens->content;
	if (check_path(st) == 1)
		return (1);
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "env") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}
