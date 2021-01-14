#include "../include/minishell.h"

int ft_exit(shell *st)
{
	int	 i;
	int  a;
	long long result;
	char *tmp;

	tmp = NULL;
	i = 0;
	a = 0;
	result = 0;
	if (!st->tokens->next)
		return (1);
//	printf("tok |%s|\n", (char *)st->tokens->next->content);
	if (st->tokens->next)
	{
		i = 0;
		tmp = ft_strdup((char *)st->tokens->next->content);
//		printf("tokbcl |%s|\n", (char *)st->tokens->next->content);
		a = 0;
		while (tmp[i])
		{
		//	printf("1|%c|\n", tmp[i]);
			while ((tmp[i] && ((tmp[i] >= 7 && tmp[i] <= 13) || tmp[i] == ' ')) && a == 0)
				i++;
			while ((tmp[i] && ((tmp[i] >= 7 && tmp[i] < 13) || tmp[i] == ' ')) && a == 1)
				i++;
			if (tmp[i] && ft_isdigit(tmp[i]))
				a = 1;
			if (tmp[i] && !ft_isdigit(tmp[i]))
			{
				if ((tmp[i] == '-' || tmp[i] == '+') && ft_isdigit(tmp[i + 1]))
					(void)i;
				else
				{
					write(1, "minishell: ", 11);
					write(1, "exit: ", 6);
					write(1, tmp, ft_strlen(tmp));
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
	result = ft_atoi(tmp);
//	printf("i |%i|\n", i);
	if (result == -1)
	{
		write(1, "minishell: ", 11);
		write(1, "exit: ", 6);
		write(1, tmp, ft_strlen(tmp));
		write(1, ": numeric argument required\n", 28);
		st->status = 255;
		return (1);
	}
	st->status = result;
	return (1);
}