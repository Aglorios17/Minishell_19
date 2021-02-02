/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_echo_n(t_shell *st, char *tm, t_list *tmp, int i)
{
	while (st->tokens->next != NULL)
	{
		tmp = st->tokens->next;
		if (!(ft_strncmp((char *)tmp->content, "-n", 2)))
		{
			i = 1;
			tm = (char *)tmp->content;
			while (tm[i] && tm[i] == 'n')
			{
				i++;
			}
			if (i == (int)ft_strlen((char *)tmp->content))
				st->tokens = tmp;
			else
			{
				i = 0;
				break ;
			}
		}
		else
			break ;
	}
	st->tokens = st->tokens->next;
	return (i);
}

int	ft_echo(t_shell *st)
{
	t_list	*tmp;
	char	*tm;
	int		i;

	tmp = NULL;
	tm = NULL;
	i = 0;
	i = ft_echo_n(st, tm, tmp, i);
	while (st->tokens != NULL)
	{
		ft_putendl_fd((char *)st->tokens->content, 1);
		st->tokens = st->tokens->next;
		if (st->tokens != NULL)
			write(1, " ", 1);
	}
	if (i == 0)
		write(1, "\n", 1);
	st->status = 0;
	return (0);
}
