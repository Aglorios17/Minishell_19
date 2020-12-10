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
		if (tmp2[b] == '\\' && ft_strchr("\\$\"", tmp2[b + 1]))
			b++;
		fri = st->tmpq;
		st->tmpq = ft_charjoin(st->tmpq, tmp2[b]);
		free(fri);
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

	a = 0;
	fri = NULL;
	new = ft_strdup("");
	st->tmpq = NULL;
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
			new = ft_charjoin(fri, tmp[a]);
		}
		free(fri);
		a++;
	}
	return (new);
}

int    ft_cleantokens(shell *st)
{
    char *tmp;
	char *fri;
    int    i;

	st->quotes = 0;
    tmp = 0;
	fri = NULL;
    i = 0;
    st->firsttok = st->tokens;
	tmp = (char*)st->tokens->content;
	st->tokens->content = ft_clean_firsttoken(st, tmp);
    if (!ft_checkcommand(st))
    {
        write(1, "minishell: ", 11);
        write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
        write(1, ": command not found\n", 20);
        st->ret = 1;
        return (0);
    }
	tmp = 0;
	st->tmpq = NULL;
    if (!st->tokens->next)
        return (0);
    st->tokens = st->tokens->next;
    while (st->tokens)
    {
        tmp = (char *)st->tokens->content;
        st->new = ft_strdup("");
        i = 0;
        while (tmp && tmp[i])
        {
			fri = st->new;
//			printf("tmp[i] : %c\n", tmp[i]);
			if (tmp[i] == '"')
			{
			//	printf("1\n");
				i = ft_double_quote(st, tmp, i);
			//	printf("2\n");
				st->new = ft_strjoin(st->new, st->tmpq);
			//	printf("3\n");
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
	/*			if (tmp[i] == '$')
				{
					st->new = ft_strjoin(fri, ft_dollars(st, tmp, i));
					i = ft_strlen(ft_dollars(st, tmp, i));
			//		printf("i|%i|\n", i);
			//		printf("new|%li|\n", ft_strlen(st->new));
					break;
				}
				else
				{
		*/
			//		printf("new\n");
				st->new = ft_charjoin(fri, tmp[i]);
		//		}
			}
			free(fri);
            i++;
        }
        st->tokens->content = st->new;
        st->tokens = st->tokens->next;
    }
	if (st->quotes%2 == 1)
	{
		fri = ft_strdup("minishell: unexpected EOF while looking for matching `\"\'\n");
       	write(1, fri, ft_strlen(fri));
		free(fri);
		return (-1);
	}
	if (st->quotes2%2 == 1)
	{
		fri = ft_strdup("minishell: unexpected EOF while looking for matching `\'\'\n");
       	write(1, fri, ft_strlen(fri));
		free(fri);
		return (-1);
	}
    st->tokens = st->firsttok;
    return (0);
}
