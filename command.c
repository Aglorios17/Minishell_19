#include "minishell.h"

char *ft_pwd(shell *st)
{
	char *buf;
	
	buf = NULL;
	st->pwd = getcwd(buf, 65535);
	return (st->pwd);
}

int ft_cd(shell *st)
{
	int i;
	char *tmp;
	char *line;

	i = 0;
	line = st->tokens->next->content;
	while (line[i] == ' ')
		i++;
	i += 2;
	while (line[i] == ' ')
		i++;
	if (!(ft_strncmp(&line[i], "..", 2)))
	{
		tmp = ft_strjoin(st->pwd, "/");
		st->pwd = ft_strjoin(tmp, &line[i]);
		free(tmp);
	}
	else if (!(ft_strncmp(&line[i], "/", 1)))
		st->pwd = "/";
	else if (!line[i])
		st->pwd = st->home;
	else
	{
		tmp = ft_strjoin(st->pwd, "/");
		st->pwd = ft_strjoin(tmp, &line[i]);
		free(tmp);	
	}
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
//	int i;

//	i = 0;
//	printf("%s\n", (char *)st->tokens->content);
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
		if (!ft_cd(st))
			return (0);
	}
	else if (!ft_strncmp((char *)st->tokens->content, "export", 7))
		ft_export(st, envp);
	else if (!ft_strncmp((char *)st->tokens->content, "unset", 6))
		ft_unset(st);
	else if (!ft_strncmp((char *)st->tokens->content, "env", 4))
	{
		while (st->envv)
		{
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
		if (!ft_exec(st))
			st->ret = 1;	
	}
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
		return (1);
	else
		return (0);
}
