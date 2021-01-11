#include "minishell.h"

int ft_exit(shell *st)
{
	int	 i;
	char *tmp;
	char *val;

	tmp = NULL;
	val = NULL;
	i = 0;
	if (!st->tokens->next)
		return (1);
	val = ft_strdup("");
	i = 0;
	tmp = ft_strdup((char *)st->tokens->next->content);
//	printf("tmp |%s|\n", tmp);
	while (tmp[i] == ' ')
		i++;
	while (tmp[i] == '0' && tmp[i + 1] != '\0')
		i++;
	while (tmp[i])
	{
		while (tmp[i] == ' ')
			i++;
		if (tmp[i] == '0' && (tmp[i - 1] == '-' || tmp[i - 1] == '+') && tmp[i + 1] != '\0')
		{
			while (tmp[i] == '0')
				i++;
		}
		if (tmp[i] == '\\' && ft_strchr("tfr", tmp[i + 1]))
			i += 2;
		else if (tmp[i])
		{
			val = ft_charjoin(val, tmp[i]);
			i++;
		}	
	}
	st->tokens->next->content = val;
	val = tmp;
//	printf("tok |%s|\n", (char *)st->tokens->next->content);
	if (st->tokens->next)
	{
		i = 0;
		tmp = ft_strdup((char *)st->tokens->next->content);
//		printf("tokbcl |%s|\n", (char *)st->tokens->next->content);
		while (tmp[i])
		{
//			printf("|%c|\n", tmp[i]);
			if (!ft_isdigit(tmp[i]))
			{
				if ((tmp[i] == '-' || tmp[i] == '+') && ft_isdigit(tmp[i + 1]))
					(void)i;
				else
				{
					write(1, "minishell: ", 11);
					write(1, "exit: ", 6);
					write(1, val, ft_strlen(val));
					write(1, ": numeric argument required\n", 28);
					st->status = 255;
					return (1);
				}
			}
			i++;
		}
	}
	if (st->tokens->next->next)
	{
		write(1, "minishell: ", 11);
		write(1, "exit: ", 6);
		write(1, "too many arguments\n", 19);
		st->status = 1;
		return (0);
	}
	tmp = (char *)st->tokens->next->content;
//	printf("tmp |%s|\n", tmp);
	if (tmp[0] == '-' && tmp[1] == '1' && tmp[2] == '\0')
	{
		st->status = -1;
		return (1);
	}
	i = ft_atoi(tmp);
//	printf("i |%i|\n", i);
	if (i == -1 || ft_strlen(tmp) >= 20 || ((tmp[0] == '-' || tmp[0] == '+') && ft_strlen(tmp) >= 20))
	{
		write(1, "minishell: ", 11);
		write(1, "exit: ", 6);
		write(1, tmp, ft_strlen(tmp));
		write(1, ": numeric argument required\n", 28);
		st->status = 255;
		return (1);
	}
	st->status = i;
	return (1);
}
