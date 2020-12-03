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
	//printf("|%c|", line[i]);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\'' && line[i] != '"')
			i++;
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i + 1] == ' ' || line[i + 1] == '\0')
				return i + 1;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i + 1] == ' ' || line[i + 1] == '\0')
				return i + 1;
		}
		else if (line[i] == ' ' || line[i] == '\t')
			return i;
	}
	return i;
}

int ft_tokens(shell *st)
{
	int i;

	i = 0;
	if (st->line[0] == '\0')
		return (1);
	while (st->line[i])
	{
		while (st->line[i] == ' ' || st->line[i] == '\t')
		{
			if (st->line[i + 1] == '\0')
				return (0);
			i++;
		}
		ft_lstadd_back(&st->tokens, ft_lstnew(ft_substr(st->line, i, ft_checkspace(&st->line[i]))));
		i += ft_checkspace(&st->line[i]);
	}
	st->firsttok = st->tokens;
/*	while (st->tokens != NULL)
	{
		printf("tokens|%s|\n", (char *)st->tokens->content);
		st->tokens = st->tokens->next;
	}
	st->tokens = st->firsttok;
*/
	return (0);
}

int	ft_checkcommand(shell *st)
{
	char *tmp;

	tmp = (char *)st->tokens->content;
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "env") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
		return (1);
	else
		return (0);
}

int ft_double_quote(shell *st, char *tmp, int a)
{
	char	*tmp2;
	int 	b;
	int		c;

	tmp2 = NULL;
	st->tmpq = ft_strdup("");
	b = a;
	c = 0;
	a++;
//	printf("ok\n");
	while (tmp[a])
	{
//		printf("tmp[a] : %c\n", tmp[a]);
		if (tmp[a] == '"' && tmp[a - 1] != '\\')
		{
//			printf("ok2\n");
			tmp2 = ft_substr(tmp, b + 1, c);
//			printf("tmp2 : %s\n", tmp2);
			break;
		}
		c++;
		a++;
	}
	b = 0;
//	printf("ok3\n");
//	printf("tmp2 : %s\n", tmp2);
	while (tmp2[b])
	{
		if (tmp2[b] == '\\' && tmp2[b + 1] == '"')
			b++;
		st->tmpq = ft_charjoin(st->tmpq, tmp2[b]);
		b++;
	}
	return (a);
}

int ft_simple_quote(shell *st, char *tmp, int a)
{
	int b;
	int c;

	b = a;
	c = 0;
	st->tmpq = NULL;
//	printf("ok\n");
	a++;
	while (tmp[a])
	{
//		printf("ok2\n");
		if (tmp[a] == '\'')
		{
//			printf("ok3\n");
			st->tmpq = ft_substr(tmp, b + 1, c);
//			printf("tmp[i] 2 : %c\n", tmp[a + 1]);
			return (a);
//			printf("ok4\n");
		}
		c++;
		a++;
	}
	return (a);
}

int    ft_cleantokens(shell *st)
{
    char *tmp;
    int    i;

    tmp = 0;
    i = 0;
    st->firsttok = st->tokens;
	tmp = (char*)st->tokens->content;
	if ((tmp[0] == '"' && tmp[ft_strlen(tmp) - 1] == '"') || (tmp[0] == '\'' && tmp[ft_strlen(tmp) - 1] == '\''))
		st->tokens->content = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
    if (!ft_checkcommand(st))
    {
        write(1, "minishell: ", 11);
        write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
        write(1, ": command not found\n", 20);
        st->ret = 1;
        return (0);
    }
	tmp = 0;
    if (!st->tokens->next)
        return (0);
    st->tokens = st->tokens->next;
    while (st->tokens)
    {
        tmp = (char *)st->tokens->content;
        st->new = ft_strdup("");
        i = 0;
 //      if (ft_ifquote(st, tmp) == 1)
 //           return (0);
        while (tmp[i])
        {
//			printf("tmp[i] : %c\n", tmp[i]);
			if (tmp[i] == '"')
			{
				i = ft_double_quote(st, tmp, i);
				st->new = ft_strjoin(st->new, st->tmpq);
			}
			else if (tmp[i] == '\'')
			{
                i = ft_simple_quote(st, tmp, i);
				st->new = ft_strjoin(st->new, st->tmpq);
			}
			else
			{
				if (tmp[i] == '\\')
					i++;
				st->new = ft_charjoin(st->new, tmp[i]);
			}
            i++;
        }
        st->new[i] = '\0';
        st->tokens->content = st->new;
        st->tokens = st->tokens->next;
    }
    st->tokens = st->firsttok;
    return (0);
}

int main(int argc, char **argv, char **envp)
{
	shell	st;
	t_list	*tmp;

	st.ret = 0;
	st.quotes = 0;
	st.line = NULL;
	st.pwd = NULL;
	st.home = NULL;
	st.firsttok = NULL;
	st.tmpq = NULL;
	tmp = NULL;
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
			ft_tokens(&st);
			if (st.tokens)
				ft_cleantokens(&st);
			if (ft_command(&st, envp))
				return (0);
			free(st.line);
			st.tokens = st.firsttok;
			while (st.tokens != NULL)
			{
				free(st.tokens->content);
				st.tokens->content = NULL;
				tmp = st.tokens;
				st.tokens = st.tokens->next;
				free(tmp);
				tmp = NULL;
			}
	//		if (st.ret == 1)
	//			return (127);
		}
	}
	return (0);
}
