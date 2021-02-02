/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_init_struct_sekot(t_sekot *sekot, t_shell *st)
{
	sekot->flagcs = 0;
	sekot->i = 0;
	sekot->a = 0;
	sekot->len = 0;
	sekot->tmp = (char *)st->pipe->content;
	sekot->tmp2 = NULL;
}

void	ft_tokens2(t_sekot *sekot, char *tmp)
{
	if (tmp[sekot->i] == '>' || tmp[sekot->i] == '<')
	{
		sekot->a = sekot->i;
		sekot->len = 0;
		while (tmp[sekot->i] && (tmp[sekot->i] == '>' || tmp[sekot->i] == '<'))
		{
			sekot->i++;
			sekot->len++;
		}
		sekot->tmp2 = ft_substr(tmp, sekot->a, sekot->len);
	}
	else
	{
		sekot->a = ft_checkspace(&tmp[sekot->i], sekot);
		sekot->tmp2 = ft_substr(tmp, sekot->i, sekot->a);
		sekot->i += sekot->a;
	}
}

int		ft_tokens(t_shell *st)
{
	t_sekot	sekot;

	ft_init_struct_sekot(&sekot, st);
	if (sekot.tmp[0] == '\0')
		return (1);
	while (sekot.tmp[sekot.i])
	{
		while (sekot.tmp[sekot.i] == ' ' || sekot.tmp[sekot.i] == '\t')
		{
			if (sekot.tmp[sekot.i + 1] == '\0')
			{
				if (ft_redirections(st) == 1)
					return (1);
				return (0);
			}
			sekot.i++;
		}
		ft_tokens2(&sekot, sekot.tmp);
		ft_lstadd_back(&st->tokens, ft_lstnew(sekot.tmp2));
	}
	st->firsttok = st->tokens;
	if (ft_redirections(st) == 1)
		return (1);
	return (0);
}
