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

	i = 0;
	while (st->line[i] == ' ')
		i++;
	i += 2;
	while (st->line[i] == ' ')
		i++;
	if (!(ft_strncmp(&st->line[i], "..", 2)))
	{
		tmp = ft_strjoin(st->pwd, "/");
		st->pwd = ft_strjoin(tmp, &st->line[i]);
		free(tmp);
	}
	else if (!(ft_strncmp(&st->line[i], "/", 1)))
		st->pwd = "/";
	else if (!st->line[i])
		st->pwd = st->home;
	else
	{
		tmp = ft_strjoin(st->pwd, "/");
		st->pwd = ft_strjoin(tmp, &st->line[i]);
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
			free(tm);
		}
		else
			break;
		free(tmp);
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
	int a;
	int i;

	a = 0;
	i = 0;
//	printf("%s\n", (char *)st->tokens->content);
	if (!(ft_strncmp((char *)st->tokens->content, "echo", 4)))
		ft_echo(st);
	else if (!ft_strncmp(&st->line[i], "pwd", 4))
		write(1, ft_pwd(st), ft_strlen(ft_pwd(st)));
	else if (!ft_strncmp(&st->line[i], "cd", 2))
	{
		if (!ft_cd(st))
			return (0);
	}
	else if (!ft_strncmp(&st->line[i], "export", 6))
		write(1, "loading . . .", 13);
	else if (!ft_strncmp(&st->line[i], "unset", 5))
		write(1, "loading . . .", 13);
	else if (!ft_strncmp(&st->line[i], "env", 3))
	{
		i = 0;
		while (envp[i])
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	else if (!(ft_strncmp(&st->line[i], "exit", 4)))
		return (1);
	else
		st->ret = 1;	
	return (0);
}

int	ft_checkspace(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	return i;
}

int ft_tokens(shell *st)
{
	int i;

	i = 0;
	while (st->line[i])
	{
		if (st->line[i] == ' ' && st->line[i + 1] == '\0')
			return (0);
		while (st->line[i] == ' ')
			i++;
		ft_lstadd_back(&st->tokens, ft_lstnew(ft_substr(st->line, i, ft_checkspace(&st->line[i]))));
		i += ft_checkspace(&st->line[i]);
//		i++;
	}
//	while (st->tokens != NULL)
//	{
//		printf("%s\n", (char *)st->tokens->content);
//		st->tokens = st->tokens->next;
//	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	shell st;

	st.ret = 0;
	st.line = NULL;
	st.pwd = NULL;
	st.home = NULL;
//	write(1,"\n",1);
//	write(1,"by Aglorios and Gverhelp\n",25);
//	write(1,"\n",1);
	st.home = ft_pwd(&st);
	(void)argc;
	(void)argv;
//	st.home = "/Users/aglorios";
//	envp = 0;
	if  (argc > 1 && !ft_strncmp(argv[1], "-c", 2))
	{
		st.line = ft_strdup(argv[2]);
//		write(1,"1\n",2);
		ft_tokens(&st);
//		write(1,"2\n",2);
//		printf("%s", st.line);
		if (ft_command(&st, envp))
			return (0);
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
			ft_tokens(&st);
			if (ft_command(&st, envp))
				return (0);
		}
	}
	return (0);
}
