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

int ft_echo(shell *st, int a, int i)
{
	a = i + 4;
	while (st->line[a] == ' ')
		a++;
	if (!(ft_strncmp(&st->line[a], "-n", 2)))
	{
		st->ret = 1;
		a += 2;
	}
	while (st->line[a] == ' ')
		a++;
	while (st->line[a])
	{
		write(1, &st->line[a], 1);
		a++;
	}
	return (1);
}

int ft_command(shell *st, char **envp)
{
	int a;
	int i;

	a = 0;
	i = 0;
	if (st->ret)
		st->ret = 0;
	while (st->line[i] == ' ')
		i++;
	if (!(ft_strncmp(&st->line[i], "echo ", 5)))
		ft_echo(st, a, i);
	else if (!ft_strncmp(&st->line[i], "pwd", 4))
		write(1, ft_pwd(st), ft_strlen(ft_pwd(st)));
	else if (!ft_strncmp(&st->line[i], "cd", 2))
	{
		st->ret = 1;
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
		while (st->line[i] == ' ')
			i++;
		ft_lstadd_back(&st->tokens, ft_lstnew(ft_substr(st->line, i, ft_checkspace(&st->line[i]))));
		i += ft_checkspace(&st->line[i]);
		i++;
	}
	while (st->tokens != NULL)
	{
		printf("%s\n", (char *)st->tokens->content);
		st->tokens = st->tokens->next;
	}
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
//		if (ft_command(&st, envp))
//			return (0);
//		if (!st.ret && st.line[0] != 0)
//			write(1,"\n",1);
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
			if (!st.ret && st.line[0] != 0)
				write(1,"\n",1);
		}
	}
	return (0);
}
