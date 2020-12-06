#include "minishell.h"

int ft_double_quote(shell *st, char *tmp, int a)
{
	char	*tmp2;
	char	*fri;
	int 	b;
	int		c;

	tmp2 = NULL;
	fri = NULL;
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
		fri = st->tmpq;
		st->tmpq = ft_charjoin(fri, tmp2[b]);
		free(fri);
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

char *ft_clean_firsttoken(shell *st, char *tmp)
{
	int a;
	char *new;
	char *fri;

	a = 0;
	fri = NULL;
	new = ft_strdup("");
	st->tmpq = NULL;
	while(tmp[a])
	{
//		printf("ok\n");
		if (tmp[a] == '\'')
		{
			a = ft_simple_quote(st, tmp, a);
			fri = new;
			new = ft_strjoin(new, st->tmpq);
			free(fri);
		}
		else if (tmp[a] == '"')
		{
			a = ft_double_quote(st, tmp, a);
			fri = new;
			new = ft_strjoin(new, st->tmpq);
			free(fri);
		}
		else
		{
			if (tmp[a] == '\\')
				a++;
			fri = new;
			new = ft_charjoin(fri, tmp[a]);
			free(fri);
		}	
		a++;
	}
//	new[a] = '\0';
/*	
	a = 0;
	tmp = ft_strdup("");
	while (new[a])
	{
		while (new[a] == ' ')
			a++;
		tmp = ft_charjoin(tmp, new[a]);
//		printf("tmp : %s\n", tmp);
		a++;
	}
//	printf("new : %s\n", new);
*/
	return (new);
}

int    ft_cleantokens(shell *st)
{
    char *tmp;
	char *fri;
    int    i;

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
        while (tmp[i])
        {
			fri = st->new;
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
				st->new = ft_charjoin(fri, tmp[i]);
			}
			free(fri);
            i++;
        }
//        st->new[i] = '\0';
        st->tokens->content = st->new;
        st->tokens = st->tokens->next;
    }
    st->tokens = st->firsttok;
    return (0);
}
