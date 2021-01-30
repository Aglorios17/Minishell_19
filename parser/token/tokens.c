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

int	ft_tokens(shell *st)
{
	int		i;
	int		a;
	int		len;
	char	*fri;
	char	*tmp;

	i = 0;
	a = 0;
	len = 0;
	fri = NULL;
	tmp = NULL;
	tmp = (char *)st->pipe->content;
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
			a = i;
			len = 0;
			while (tmp[i] && (tmp[i] == '>' || tmp[i] == '<'))
			{
				i++;
				len++;
			}
			fri = ft_substr(tmp, a, len);
		}
		else
		{
			a = ft_checkspace(&tmp[i]);
			fri = ft_substr(tmp, i, a);
			i += a;
		}
		ft_lstadd_back(&st->tokens, ft_lstnew(fri));
	}
	st->firsttok = st->tokens;
	if (ft_redirections(st) == 1)
		return (1);
	return (0);
}
