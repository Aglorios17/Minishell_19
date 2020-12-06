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
