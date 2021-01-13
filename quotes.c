#include "minishell.h"

int	ft_back(char *tmp, int a)
{
	int i;

	i = 0;
	while (tmp && tmp[a])
	{
		while (tmp[a] == '\\')
		{
			i++;
			a++;
		}
		if (tmp[a] == '"')
			return (i);
		a++;
	}
	return (i);
}

int ft_double_quote(shell *st, char *tmp, int a)
{
	char	*tmp2;
	char	*fri;
	int 	b;
	int		c;
	int		bol;
	int		back;

	tmp2 = NULL;
	fri = NULL;
	st->tmpq = ft_strdup("");
	b = a;
	c = 0;
	back = 0;
	bol = a;
	a++;
	st->quotes++;
	while (tmp[a])
	{
//		printf("tmp[a] : %c\n", tmp[a]);
		if (tmp[a] == '"' /*&& tmp[a - 1] != '\\'*/)
		{
			back = ft_back(tmp, bol + 1);
//			printf("back : %i\n", back);
			if (back%2 == 0 || tmp[a - 1] != '\\')
			{
				tmp2 = ft_substr(tmp, b + 1, c);
//				printf("tmp2 : %s\n", tmp2);
				st->quotes++;
//				printf("quotes : %i\n", st->quotes);
				break;
			}
		}
		c++;
		a++;
	}
	b = 0;
//	printf("ok3\n");
//	printf("tmp2 : %s\n", tmp2);
//	printf("a : %i\n", a);
	while (tmp2 && tmp2[b])
	{
		st->flagdq = 0;
		if (tmp2[b] == '$')
		{
			st->flagdq = 1;
			ft_dollars(st, tmp2, b);
			b = st->pass;
		}
		else
		{
			if (tmp2[b] == '\\' && ft_strchr("\\$\"", tmp2[b + 1]))
				b++;
			fri = st->tmpq;
//			printf("tmp2[b] : %c\n", tmp2[b]);
			st->tmpq = ft_charjoin(st->tmpq, tmp2[b]);
//			printf("tmpq : %s\n", st->tmpq);
			free(fri);
		}
		b++;
	}
	free(tmp2);
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
	st->quotes2++;
	while (tmp[a])
	{
//		printf("ok2\n");
		if (tmp[a] == '\'')
		{
//			printf("ok3\n");
			st->tmpq = ft_substr(tmp, b + 1, c);
			st->quotes2++;
//			printf("tmp[i] 2 : %c\n", tmp[a + 1]);
			return (a);
//			printf("ok4\n");
		}
		c++;
		a++;
	}
	return (a);
}

char *ft_clean_firsttoken(shell *st, char *tmp)
{
	int a;
	char *new;
	char *fri;
	char *tmp2;

	a = 0;
	fri = NULL;
	new = ft_strdup("");
	st->tmpq = NULL;
	tmp2 = NULL;
//	printf("tmp : %s\n", tmp);
	while(tmp[a])
	{
//		printf("ok\n");
		fri = new;
		if (tmp[a] == '\'')
		{
			a = ft_simple_quote(st, tmp, a);
			new = ft_strjoin(new, st->tmpq);
		}
		else if (tmp[a] == '"')
		{
			a = ft_double_quote(st, tmp, a);
			new = ft_strjoin(new, st->tmpq);
		}
		else
		{
			if (tmp[a] == '\\' && tmp[a + 1] != '\0')
				a++;
			if (tmp[a] == '$' && tmp[a - 1] != '\\')
			{
//				printf("i4 : |%d|\n", i);
//				st->flagdq = 1;
				st->tmpq = ft_strdup("");
				st->firstd++;
				ft_dollars(st, tmp, a);
				a = st->pass;
				if (check_path(st, st->tmpq) == 1)
					return ((char *)st->tokens->content);
				else
					new = ft_strjoin(new, st->tmpq);
//				printf("i5 : |%d|\n", i);
//				printf("new 2 : |%s|\n", st->new);
//				printf("new 3 : |%s|\n", st->new);
			}
			else
				new = ft_charjoin(fri, tmp[a]);
		}
		free(fri);
		a++;
	}
	if (!st->tokens->next)
	{
		while (st->envv)
		{
			tmp2 = (char *)st->envv->content;
			if (!ft_strncmp("_=", tmp2, 2))
			{
				st->envv->content = ft_strjoin("_=", tmp);
				break;
			}
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
	}
	return (new);
}

int    ft_cleantokens(shell *st)
{
    char *tmp;
    char *tmp2;
	char *fri;
    int    i;

	st->quotes = 0;
    tmp = 0;
    tmp2 = 0;
	fri = NULL;
    i = 0;
	st->firstd = 1;
    st->firsttok = st->tokens;
	tmp = (char*)st->tokens->content;
//	printf("tmp : %s\n", tmp);
//	write(1, "1\n", 2);
	st->tokens->content = ft_clean_firsttoken(st, tmp);
//	write(1, "1\n", 2);
    if (!ft_checkcommand(st))
    {
//		printf("st->cmdexec : %s\n", st->cmdexec);
		if (st->status != 126)
		{
			if (st->pat[0] == '\0' || !st->pat)
			{
        		write(1, "minishell: ", 11);
        		write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
        		write(1, ": No such file or directory\n", 28);
			}
			else
			{
        	write(1, "minishell: ", 11);
        	write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
        	write(1, ": command not found\n", 20);
			}
			st->status = 127;
		}
//     	st->ret = 1;
        return (0);
    }
	tmp = 0;
	st->tmpq = NULL;
    if (!st->tokens->next)
        return (0);
    st->tokens = st->tokens->next;
    while (st->tokens)
    {
        tmp = ft_strdup((char *)st->tokens->content);
        st->new = ft_strdup("");
        i = 0;
//		printf("tmp |%s|\n", tmp);
        while (tmp[i] && tmp[i] != '\0')
        {
//			st->flagdq = 0;
			fri = st->new;
//			printf("i1 : |%d|\n", i);
			if (tmp[i] == '"')
			{
			//	printf("1\n");
//				printf("i2 : |%d|\n", i);
//				st->flagdq = 1;
				i = ft_double_quote(st, tmp, i);
//				printf("i3 : |%d|\n", i);
			//	printf("2\n");
				st->new = ft_strjoin(st->new, st->tmpq);
//				printf("new 1 : |%s|\n", st->new);
			//	printf("3\n");
			}
			else if (tmp[i] == '\'')
			{
                i = ft_simple_quote(st, tmp, i);
				st->new = ft_strjoin(st->new, st->tmpq);
			}
			else if (tmp[i] != '\0')
			{
			//	printf("2\n");
//				printf("tmp : |%s|\n", tmp);
				if (tmp[i] == '\\')
				{
//					if (!tmp[i + 1]) ///////////////////////////////////
//						st->new = ft_strdup(" ");
					i++;
				}
				if (tmp[i] == '$' && tmp[i - 1] != '\\')
				{

//					printf("i4 : |%d|\n", i);
					st->tmpq = ft_strdup("");
					st->firstd++;
					ft_dollars(st, tmp, i);
					i = st->pass;
//					printf("i5 : |%d|\n", i);
//					printf("new 2 : |%s|\n", st->new);
					st->new = ft_strjoin(st->new, st->tmpq);
//					printf("new 3 : |%s|\n", st->new);
				}
				else
				{
//					printf("new 4 : |%s|\n", st->new);
					st->new = ft_charjoin(fri, tmp[i]);
//					printf("new 5 : |%s|\n", st->new);
				}
			}
			free(fri);
            i++;
//			printf("len tmp : |%ld|\n", ft_strlen(tmp));
//			printf("tmp[i] : |%c|\n", tmp[i]);
        }
        st->tokens->content = st->new;
		tmp2 = (char *)st->tokens->content;
        st->tokens = st->tokens->next;
    }
	free(tmp);
	if (st->quotes%2 == 1)
	{
		fri = ft_strdup("minishell: unexpected EOF while looking for matching `\"\'\n");
       	write(1, fri, ft_strlen(fri));
		free(fri);
		st->status = 2;
		return (-1);
	}
	if (st->quotes2%2 == 1)
	{
		fri = ft_strdup("minishell: unexpected EOF while looking for matching `\'\'\n");
       	write(1, fri, ft_strlen(fri));
		free(fri);
		st->status = 2;
		return (-1);
	}
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp("_=", tmp, 2))
		{
//			printf("tmp2 ||%s||\n", tmp2);
			st->envv->content = ft_strjoin("_=", tmp2);
			break;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
    st->tokens = st->firsttok;
    return (0);
}
