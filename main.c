#include "minishell.h"
/*
int check(char *s1, char *s2)
{
	int i;
	int a;

	i = 0;
	a = ft_strlen(s2);
	while (s1[i] && s2[i])
	{
		if (s1[i] == ' ')
		{
			if (s1[i] == s2[i])
			{
				if (!ft_strncmp(s1[i], s2[i], a))
					return (i);
				i++;
			}
			i++;
		}
		else
			return (-1);
	}
	return (-1);
}
*/

char *ft_pwd(shell *st)
{
	char *buf;
	
	buf = NULL;
	st->pwd = getcwd(buf, 65535);
	return (st->pwd);
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
	}
	else if (!ft_strncmp(&st->line[i], "pwd", 3))
		write(1, ft_pwd(st), ft_strlen(ft_pwd(st)));
	else if (!ft_strncmp(&st->line[i], "cd", 2))
		write(1, "loading", 7);
	else if (!ft_strncmp(&st->line[i], "export", 6))
		write(1, "loading", 7);
	else if (!ft_strncmp(&st->line[i], "unset", 5))
		write(1, "loading", 7);
	else if (!ft_strncmp(&st->line[i], "env", 3))
		write(1, "loading", 7);
	else if (!(ft_strncmp(&st->line[i], "exit", 4)))
		return (1);
	else
		write(1, "NOP", 3);
	return (0);
}

int main()
{
	int bcl;
	int y;
	char *echo;
	shell st;

	bcl = 1;
	y = 0;
	st.ret = 0;
	st.line = NULL;
	echo = NULL;
	st.pwd = NULL;
	write(1,"\n",1);
	write(1,"by Aglorios and Gverhelp\n",25);
	write(1,"\n",1);
	while(bcl == 1)
	{
		write(1,"#",1);
		while (get_next_line3d(0, &st.line) != 1)
		{
		}
		if (ft_command(&st))
			return (0);
		if (!st.ret)
			write(1,"\n",1);
	}
	return (0);
}
