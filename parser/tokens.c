#include "../include/minishell.h"

int	ft_checkspace(char *line)
{
	int i;
	int a;

	i = 0;
	a = 0;
	//printf("|%c|", line[i]);
	while (line[i])
	{
//		printf("1|%c|\n", line[i]);
//		printf("in1  |%i|\n", i);
//		printf("111111111111111111|%c|\n", line[i]);
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\'' && line[i] != '"' && line[i] != '>' && line[i] != '<')
		{
			i++;
//			printf("in2  |%i|\n", i);
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] == '\'')
			{
				if (line[i + 1] != '\'')
					i++;
				while (line[i] && line[i] != '\'')
				{
					if (line[i] == ' ')
						return (i);
					i++;
				}
				i++;
			}
			while (line[i] && line[i] != '\'')
			{
/*
				a = i; ////////////////////////////////////////////////// modif space end string
//				printf("1|%c|\n", line[a]);
				while (line[a] == ' ' || line[a] == '\t')
				{
//					printf("2|%c|\n", line[a]);
					a++;
				}
				if (line[a] == '\0')
					return (i);
*/
				i++;
			}
			if (line[i + 1] == ' ' || line[i + 1] == '\0')
				return i + 1;
///*
			a = i + 1;
//			printf("line[a] : |%c|\n", line[a]);
			while (line[a] && line[a] != ' ' && line[a] != '\t' && line[a] != '\'' && line[a] != '\'') ////////////////// modif split tok "@"$a "@"
				a++;
//			printf("a|%c|\n", line[a]);
			if (line[a] == ' ' || line[a] == '\t')
				return (a);
//*/
		}
		else if (line[i] == '"')
		{
			i++;
//			printf("222222222222222|%c|\n", line[i]);
//			printf("1|%c|\n", line[i]);
			while (line[i] == '"')
			{	
				if (line[i + 1] != '"')
					i++;
				while (line[i] && line[i] != '"')
				{
					if (line[i] == ' ')
						return (i);
					i++;
				}
				i++;
			}
	//		printf("c1 : |%c|\n", line[i]);
			while (line[i] && line[i] != '"')
			{
/*
				a = i; ////////////////////////////////////////////////// modif space end string
//				printf("1|%c|\n", line[a]);
				while (line[a] == ' ' || line[a] == '\t')
				{
//					printf("2|%c|\n", line[a]);
					a++;
				}
				if (line[a] == '\0')
					return (i);
*/
				i++;
			}
//			printf("c2 : %d |%s|\n", i, &line[i]);
/*
			printf("c2 : |%c| \n", line[i - 1]);
			printf("c3 : |%c| \n", line[i]);
			printf("c4 : %d |%s|\n", i, &line[i]);
*/
			if (line[i] && line[i] == '"' && line[i - 1] == '\\') //////// modif tokens = " \" "
				i++;
			a = i + 1;
			if (line[a] == '"' && line[a - 1] != '"')
				return (a + 1);
//			printf("c2 : |%c| \n", line[a - 1]);
//			printf("c3 : |%c| \n", line[a]);
//			printf("c4 : %d |%s|\n", a, &line[a]);
//			if (line[a] && line[a] == '"' && line[a - 1] == '\\') //////// modif tokens = " \" "
//				a++;		
//			printf("c3 : %d |%c|\n", a, line[a]);
			while (line[a] && line[a] != ' ' && line[a] != '\t' && line[a] != '"' && line[a] != '\'') ////////////////// modif split tok "@"$a "@"
				a++;
//			printf("c2 : |%c| \n", line[a - 1]);
//			printf("c3 : |%c| \n", line[a]);
//			if (line[a] && line[a] == '"' && line[a - 1] == '\\') //////// modif tokens = " \" "
//				a++;
//			printf("c4 : %d |%c|\n", a, line[a]);
//			printf("a|%c|\n", line[a]);
			if (line[a] == ' ' || line[a] == '\t')
				return (a);
//*/
		}
		else if (line[i] == '>' || line[i] == '<')
			return (i);
		else if (line[i] == ' ' || line[i] == '\t')
		{
			(void)a;
//			printf("in3  |%i|\n", i);
			if (line[i - 1] == '\\')
				i++;
			else
				return i;
		}
/*		else
		{
			a = i;
			printf("1|%c|\n", line[a]);
			while (line[a] == ' ' || line[a] == '\t')
			{
				printf("2|%c|\n", line[a]);
				a++;
			}
			if (line[a] == '\0')
				return (i);
		}*/
	}
	return (i);
}

int ft_tokens(shell *st)
{
	int i;
	int a;
	int b;
	int len;
	char *fri;
	char *tmp;

	i = 0;
	a = 0;
	b = 0;
	len = 0;
	fri = NULL;
	tmp = NULL;
	tmp = (char *)st->pipe->content;
//	printf("cultine->content |%s|\n", (char *)st->cutline->content);
	if (tmp[0] == '\0')
		return (1);
	while (tmp[i])
	{
		while (tmp[i] == ' ' || tmp[i] == '\t')
		{
			if (tmp[i + 1] == '\0')
			{
				if (ft_redirections(st) == 1)
					return (1);
				return (0);
			}
			i++;
		}
		if (tmp[i] == '>' || tmp[i] == '<')
		{
			b = i;
			len = 0;
//			printf("tmp[b] |%c|\n", tmp[b]);
			while(tmp[i] && (tmp[i] == '>' || tmp[i] == '<'))
			{
//				printf("tmp[i] |%c|\n", tmp[i]);
				i++;
				len++;
			}
			fri = ft_substr(tmp, b, len);
//			printf("fri |%s|\n", fri);
		}
		else
		{
			fri = ft_substr(tmp, i, a = ft_checkspace(&tmp[i]));
			i += a;
		}
//		printf("aacheck  |%i|\n", a);
//		printf("tokkkkk  |%s|\n", fri);
//		printf("iiiiiii  |%i|\n", i);
		ft_lstadd_back(&st->tokens, ft_lstnew(fri));
//		free(fri);
//		fri = NULL;
//		i += a; //ft_checkspace(&tmp[i]);
	}
/*	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "_=", 2))
		{
	//		printf("envv|%s|\n", (char *)st->envv->content);
	//		printf("tokens|%s|\n", (char *)st->tokens->content);
			st->envv->content = ft_strjoin("_=", (char *)st->tokens->content);
			break;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
*/
	st->firsttok = st->tokens;
	if (ft_redirections(st) == 1)
		return (1);
/*
	while (st->tokens != NULL)
	{
	//	tmp = ft_strdup((char *)st->tokens->content);
	//	if (tmp[ft_strlen(tmp) - 1] == '\\')
	//		st->tokens->content = ft_strjoin(ft_substr(tmp, 0, ft_strlen(tmp) - 1), " ");
		printf("tokens|%s|\n", (char *)st->tokens->content);
		st->tokens = st->tokens->next;
	}
	st->tokens = st->firsttok;
*/
	return (0);
}
