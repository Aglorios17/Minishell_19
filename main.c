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

int ft_command(shell *st)
{
	int a;
	int i;

	a = 0;
	i = 0;
	if (st->ret)
		st->ret = 0;
	while (st->line[i] == ' ')
		i++;
	if (!(ft_strncmp(&st->line[i], "echo", 4)))
		ft_echo(st, a, i);
	else if (!ft_strncmp(&st->line[i], "pwd", 3))
		write(1, ft_pwd(st), ft_strlen(ft_pwd(st)));
	else if (!ft_strncmp(&st->line[i], "cd", 2))
	{
		st->ret = 1;
		if (!ft_cd(st))
		{
		//	write(1, "", 3);
			return (0);
		}
	}
	else if (!ft_strncmp(&st->line[i], "export", 6))
		write(1, "loading . . .", 13);
	else if (!ft_strncmp(&st->line[i], "unset", 5))
		write(1, "loading . . .", 13);
	else if (!ft_strncmp(&st->line[i], "env", 3))
		write(1, "loading . . .", 13);
	else if (!(ft_strncmp(&st->line[i], "exit", 4)))
		return (1);
	else
		st->ret = 1;	
//		write(1, "NOP", 3);
	return (0);
}

int main()
{
	int y;
	char *echo;
	shell st;

	y = 0;
	st.ret = 0;
	st.line = NULL;
	echo = NULL;
	st.pwd = NULL;
	st.home = NULL;
	write(1,"\n",1);
	write(1,"by Aglorios and Gverhelp\n",25);
	write(1,"\n",1);
	st.home = ft_pwd(&st);
//	if (argc == 3 && ft_strncmp(argv[1],"-c", 3))
//	{
		while(1)
		{
			write(1,">>",2);
			if (get_next_line3d(0, &st.line) != 1)
			{
				write(1, "exit\n", 5);
				return(0);
			}
			if (ft_command(&st))
				return (0);
			if (!st.ret && st.line[0] != 0)
				write(1,"\n",1);
		}
//	}
	return (0);
}
