#include "../include/minishell.h"

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
//	char	*fri;
	char	*re;
	int 	b;
	int		c;
	int		bol;
	int		back;

	tmp2 = NULL;
//	fri = NULL;
	re = NULL;
	st->tmpq = ft_strdup("");
	b = a;
	c = 0;
	back = 0;
	bol = a;
	a++;
	st->quotes++;
	while (tmp[a])
	{
		if (tmp[a] == '"')
		{
			back = ft_back(tmp, bol + 1);
			if (back%2 == 0 || tmp[a - 1] != '\\')
			{
				tmp2 = ft_substr(tmp, b + 1, c);
				st->quotes++;
				break;
			}
		}
		c++;
		a++;
	}
	b = 0;
	re = ft_strdup("");
	while (tmp2 && tmp2[b])
	{
		st->flagdq = 0;
		if (tmp2[b] == '$')
		{
			st->flagdq = 1;
			ft_dollars(st, tmp2, b);
			re = ft_strjoin(re, st->tmpq);
			b = st->pass;
			st->flagdq = 0;
		}
		else
		{
			if (tmp2[b] == '\\' && ft_strchr("\\$\"", tmp2[b + 1]))
				b++;
//			fri = st->tmpq;
			re = ft_charjoin(re, tmp2[b]);
//			free(fri);
		}
		b++;
	}
	st->tmpq = ft_strdup(re);
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
	a++;
	st->quotes2++;
	while (tmp[a])
	{
		if (tmp[a] == '\'')
		{
			st->tmpq = ft_substr(tmp, b + 1, c);
			st->quotes2++;
			return (a);
		}
		c++;
		a++;
	}
	return (a);
}

char *ft_clean_firsttoken(shell *st, char *tmp)
{
	int a;
	int b;
	char *new;
	char *fri;
	char *tmp2;
	char *back;

	a = 0;
	b = 0;
	fri = NULL;
	new = ft_strdup("");
	st->tmpq = NULL;
	tmp2 = NULL;
	back = NULL;
	st->ret = 0;
//	printf("tmp : %s\n", tmp);
	while(tmp[a])
	{
//		printf("ok\n");
		fri = new;
		if (tmp[a] == '\'')
		{
			a = ft_simple_quote(st, tmp, a);
			new = ft_strjoin(new, st->tmpq);
			tmp = ft_strjoin(new, &tmp[a + 1]);
			a = ft_strlen(new) - 1;
		}
		else if (tmp[a] == '"')
		{
			a = ft_double_quote(st, tmp, a);
			new = ft_strjoin(new, st->tmpq);
			tmp = ft_strjoin(new, &tmp[a + 1]);
			a = ft_strlen(new) - 1;
		}
		else
		{
			b = 0;
			if (tmp[a] == '\\')
			{
				b = 0;
				back = ft_strdup("");
				while (b < a)
				{
					back = ft_charjoin(back, tmp[b]);
					b++;
				}
				tmp = ft_strjoin(back, &tmp[a + 1]);
				b = 1;
			}
			if (tmp[a] == '$' && b == 0 && tmp[a + 1] != '\\')
			{
				st->tmpq = ft_strdup("");
				st->firstd++;
				ft_dollars(st, tmp, a);
				new = ft_strdup(st->tmpq);
				tmp = ft_strjoin(new, &tmp[st->pass + 1]);
				a = ft_strlen(new) - 1;
			}
			else
			{
				new = ft_charjoin(fri, tmp[a]);
				tmp = ft_strjoin(new, &tmp[a + 1]);
			}
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
//	printf("new|%s|\n", new);
	return (tmp);
}

int    ft_cleantokens(shell *st)
{
    char	*tmp;
    char	*tmp2;
	char	*fri;
	char	*back;
    int		i;
	int		b;

	st->quotes = 0;
    tmp = 0;
    tmp2 = 0;
	fri = NULL;
	back = NULL;
    i = 0;
	b = 0;
	st->firstd = 1;
    st->firsttok = st->tokens;
	tmp = (char*)st->tokens->content;
	st->tokens->content = ft_clean_firsttoken(st, tmp);
//	printf("st->tokens->content|%s|\n", (char *)st->tokens->content);
//	ft_clean_firsttoken(st, tmp);
//	printf("|ok1|\n");
    if (!ft_checkcommand(st))
    {
//		printf("|ok2|\n");
//		if (st->status != 126)
//		{
//			printf("|ok3|\n");
//			if (st->pat[0] == '\0')
//			{
//				printf("|ok4|\n");
//        		write(1, "minishell: ", 11);
// 	    		write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
//        		write(1, ": No such file or directory\n", 28);
//			}
//			else
//			{
//        		write(1, "minishell: ", 11);
// 	    		write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
//	       		write(1, ": command not found\n", 20);
//			}
//			st->status = 127;
//		}
        return (0);
    }
	tmp = 0;
	st->tmpq = NULL;
    if (!st->tokens->next)
        return (0);
    st->tokens = st->tokens->next;
    while (st->tokens)
    {
	//	printf("|ok|\n");
		tmp = NULL;
        tmp = ft_strdup((char *)st->tokens->content);
	//	printf("|ok2|\n");
        st->new = ft_strdup("");
        i = 0;
        while (tmp[i] && tmp[i] != '\0')
        {
		//	printf("&tmp[i]debut|%s|\n", &tmp[i]);
			if (tmp[i] == '"')
			{
				i = ft_double_quote(st, tmp, i);
				st->new = ft_strjoin(st->new, st->tmpq);
			//	printf("st->new|%s|\n", st->new);
			//	printf("after|%s|\n", &tmp[i + 1]);
				tmp = ft_strjoin(st->new, &tmp[i + 1]);
			//	printf("tmp|%s|\n", tmp);
				i = ft_strlen(st->new) - 1;
			}
			else if (tmp[i] == '\'')
			{
                i = ft_simple_quote(st, tmp, i);
				st->new = ft_strjoin(st->new, st->tmpq);
			//	printf("st->new|%s|\n", st->new);
			//	printf("after|%s|\n", &tmp[i + 1]);
				tmp = ft_strjoin(st->new, &tmp[i + 1]);
				i = ft_strlen(st->new) - 1;
			}
			else if (tmp[i] != '\0')
			{
			//	(void)back;
				b = 0;
				if (tmp[i] == '\\')
				{
					b = 0;
					back = ft_strdup("");
					while (b < i)
					{
						back = ft_charjoin(back, tmp[b]);
						b++;
					}
					tmp = ft_strjoin(back, &tmp[i + 1]);
					b = 1;
				}
				if (tmp[i] == '$' && b == 0 && tmp[i + 1] != '\\')
				{
			//		printf("&tmp[i]|%s|\n", &tmp[i]);
					st->ret = 0;
					st->tmpq = ft_strdup("");
					st->firstd++;
					ft_dollars(st, tmp, i);
//					printf("/////////////////////st->new 1: %s\n", st->new);
					st->new = ft_strdup(st->tmpq);
//					printf("/////////////////////st->new 2: %s\n", st->new);
					if (st->ret == 0)
						tmp = ft_strjoin(st->new, &tmp[st->pass + 1]);
					else
						tmp = ft_strdup(st->new);
					i = ft_strlen(st->new) - 1;
//					printf("/////////////////////st->new 3: %s\n", st->new);
//					printf("&tmp[i]|%s|\n", &tmp[i]);
//					printf("&tmp[i + 1]|%s|\n", &tmp[i + 1]);
				}
				else
				{
					st->new = ft_charjoin(st->new, tmp[i]);
				//	printf("st->new : %s\n", st->new);
				//	printf("&tmp[i]|%s|\n", &tmp[i + 1]);
					tmp = ft_strjoin(st->new, &tmp[i + 1]);
				}
			}
		//	free(fri);
		//	printf("tmp|%s|\n", tmp);
		//	printf("tmp[i]|%c|\n", tmp[i]);
            i++;
		//	printf("/////////////tmp[i]2|%c|\n", tmp[i]);
        }
	//	printf("tmpfin|%s|\n", tmp);
        st->tokens->content = ft_strdup(tmp);
	//	printf("tmptok|%s|\n", (char *)st->tokens->content);
	//	printf("tmptok2|%s|\n", (char *)st->tokens->next->content);
		tmp2 = (char *)st->tokens->content;
		st->ddone += 1;
		while (st->tokens && st->ddone != 0)
		{
	//		printf("tmptok|%s|\n", (char *)st->tokens->content);
        	st->tokens = st->tokens->next;
			st->ddone -= 1;
		}
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
