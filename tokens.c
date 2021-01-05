#include "minishell.h"

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
				i++;
			if (line[i + 1] == ' ' || line[i + 1] == '\0')
				return i + 1;
		}
		else if (line[i] == '"')
		{
			i++;
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
				i++;
	//		printf("c2 : |%c|\n", line[i]);
			if ((line[i + 1] == ' ' && line[i - 1] != '\\') || line[i + 1] == '\0') //////// modif tokens = " \" "
				return i + 1;
		}
		else if (line[i] == ' ' || line[i] == '\t')
		{
			if (line[i - 1] == '\\')
				i++;
			else
				return i;
		}
	}
	return i;
}

int ft_tokens(shell *st)
{
	int i;
	char *fri;
	char *tmp;

	i = 0;
	fri = NULL;
	tmp = NULL;
	tmp = (char *)st->cutline->content;
//	printf("|%s|\n", (char *)st->cutline->content);
	if (tmp[0] == '\0')
		return (1);
	while (tmp[i])
	{
		while (tmp[i] == ' ' || tmp[i] == '\t')
		{
			if (tmp[i + 1] == '\0')
				return (0);
			i++;
		}
		fri = ft_substr(tmp, i, ft_checkspace(&tmp[i]));
		ft_lstadd_back(&st->tokens, ft_lstnew(fri));
//		free(fri);
//		fri = NULL;
		i += ft_checkspace(&tmp[i]);
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
