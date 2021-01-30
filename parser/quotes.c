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
	char	*re;
	char	*fri;
	int 	b;
	int		c;
	int		bol;
	int		back;

	tmp2 = ft_strdup("");
	fri = NULL;
	re = NULL;
	if (st->tmpq)
		free(st->tmpq);
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
				free(tmp2);
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
		if (st->rd == 1 && tmp2[b] == '$')
		{
			st->flagdq = 1;
			ft_dolredic(st, tmp2, b);
			fri = re;
			re = ft_strjoin(re, st->tmpq);
			free(fri);
			b = st->pass;
			st->flagdq = 0;
		}
		else if (st->rd == 0 && tmp2[b] == '$')
		{
			st->flagdq = 1;
			ft_dollars(st, tmp2, b);
			fri = re;
			re = ft_strjoin(re, st->tmpq);
			free(fri);
			b = st->pass;
			st->flagdq = 0;
		}
		else
		{
			if (tmp2[b] == '\\' && ft_strchr("\\$\"", tmp2[b + 1]))
				b++;
			fri = re;
			re = ft_charjoin(re, tmp2[b]);
			free(fri);
		}
		b++;
	}
	free(st->tmpq);
	st->tmpq = ft_strdup(re);
	free(re);
	free(tmp2);
	return (a);
}

int ft_simple_quote(shell *st, char *tmp, int a)
{
	int b;
	int c;

	b = a;
	c = 0;
	a++;
	st->quotes2++;
	while (tmp[a])
	{
		if (tmp[a] == '\'')
		{
			free(st->tmpq);
			st->tmpq = ft_substr(tmp, b + 1, c);
			st->quotes2++;
			return (a);
		}
		c++;
		a++;
	}
	return (a);
}

char *ft_traduction(shell *st, char *tmp)
{
	int		i;
	int		b;
	char	*back;
	char	*fri;
	
	i = 0;
	b = 0;
	back = NULL;
	st->tmpq = ft_strdup("");
	fri = NULL;
    st->new = ft_strdup("");
	while (tmp[i] && tmp[i] != '\0')
	{
		if (tmp[i] == '"')
		{
			i = ft_double_quote(st, tmp, i);
			fri = st->new;
			st->new = ft_strjoin(st->new, st->tmpq);
			free(fri);
			tmp = ft_strjoin(st->new, &tmp[i + 1]);                                 ////// here
			i = ft_strlen(st->new) - 1;
		}
		else if (tmp[i] == '\'')
		{
			i = ft_simple_quote(st, tmp, i);
			fri = st->new;
			st->new = ft_strjoin(st->new, st->tmpq);
			free(fri);
			tmp = ft_strjoin(st->new, &tmp[i + 1]);                                   ////// here
			i = ft_strlen(st->new) - 1;
		}
		else if (tmp[i] != '\0')
		{
			b = 0;
			if (tmp[i] == '\\')
			{
				b = 0;
				back = ft_strdup("");
				while (b < i)
				{
					fri = back;
					back = ft_charjoin(back, tmp[b]);
					free(fri);
					b++;
				}
				tmp = ft_strjoin(back, &tmp[i + 1]);
				free(back);
				b = 1;
			}
			if (st->rd == 1 && (tmp[i] == '$' && b == 0 && tmp[i + 1] != '\\' &&
				(ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '_' || tmp[i + 1] == '?')))
			{
				st->ret = 0;
				free(st->tmpq);
				st->tmpq = ft_strdup("");                                                       //// here
				st->firstd++;
				ft_dolredic(st, tmp, i);
				free(st->new); 
				st->new = ft_strdup(st->tmpq);
				if (st->ret == 0)
				{
					tmp = ft_strjoin(st->new, &tmp[st->pass + 1]);                            ///// here
				}
				else
				{
					tmp = ft_strdup(st->new);                                                   //// here
				}
				i = ft_strlen(st->new) - 1;
			}
			else if (st->rd == 0 && (tmp[i] == '$' && b == 0 && tmp[i + 1] != '\\' &&
				(ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '_' || tmp[i + 1] == '?')))
			{
				st->ret = 0;
				free(st->tmpq);
				st->tmpq = ft_strdup("");                                                       //// here
				st->firstd++;
				ft_dollars(st, tmp, i);
				free(st->new); 
				st->new = ft_strdup(st->tmpq);
				if (st->ret == 0)
				{
					tmp = ft_strjoin(st->new, &tmp[st->pass + 1]);                            ///// here
				}
				else
				{
					free(tmp);
					tmp = ft_strdup(st->new);
				}
				i = ft_strlen(st->new) - 1;
			}
			else
			{
				fri = st->new;
				st->new = ft_charjoin(st->new, tmp[i]);
				free(fri);
			}
		}
		i++;
	}
	free(st->new);
//	free(st->tmpq);
	return (tmp);
}

int    ft_cleantokens(shell *st)
{
    char	*tmp;
    char	*tmp2;
	char	*fri;
	int		i;

	st->quotes = 0;
	i = 0;
    tmp = 0;
    tmp2 = 0;
	fri = NULL;
	st->firstd = 1;
	st->ddone = 0;
    st->firsttok = st->tokens;
	tmp = ft_strdup((char*)st->tokens->content);
    st->tokens->content = ft_strdup(ft_traduction(st, tmp));                                   //// here
	free(tmp);
	if (!st->tokens->next)
	{
		while (st->envv)
		{
			tmp = (char *)st->envv->content;
			if (!ft_strncmp("_=", tmp, 2))
			{
				st->envv->content = ft_strjoin("_=", (char *)st->tokens->content);                  //// here
				break;
			}
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
	}
    if (!(ft_checkcommand(st)))
		return (0);
    if (!st->tokens->next)
        return (0);
    st->tokens = st->tokens->next;
    while (st->tokens)
    {
        tmp = ft_strdup((char *)st->tokens->content);											//// here
        st->tokens->content = ft_strdup(ft_traduction(st, tmp));                                //// here
		tmp2 = (char *)st->tokens->content;
		st->ddone += 1;
		while (st->tokens && st->ddone != 0)
		{
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
//			printf("tok ||%s||\n", (char *)st->firsttok->content);
//			(void)i;
			if (!ft_strcmp((char *)st->firsttok->content, "export"))
			{
				st->envv->content = ft_strdup("");                                                 /// here
				i = 0;
				while (tmp2[i] && tmp2[i] != '=')
				{
					st->envv->content = ft_charjoin((char *)st->envv->content, tmp2[i]);			//// here
					i++;
				}
				st->envv->content = ft_strjoin("_=", (char *)st->envv->content);					//// here
			}
			else
				st->envv->content = ft_strjoin("_=", tmp2);											/// here
			break;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
    st->tokens = st->firsttok;
    return (0);
}

int	ft_checkcommand(shell *st)
{
	char *tmp;

	tmp = (char *)st->tokens->content;
//	printf("|ok|\n");
	if (check_path(st, tmp) == 1)
		return (1);
//	printf("|ok2|\n");
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "env") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}