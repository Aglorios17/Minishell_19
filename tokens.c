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
			while (line[i] && line[i] != '"')
				i++;
			if (line[i + 1] == ' ' || line[i + 1] == '\0')
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
	st->firsttok = st->tokens;
/*	
	while (st->tokens != NULL)
	{
		printf("tokens|%s|\n", (char *)st->tokens->content);
		st->tokens = st->tokens->next;
	}
	st->tokens = st->firsttok;
*/
	return (0);
}
