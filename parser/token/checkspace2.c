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

int	ft_checkifsimplequote3(char *line, int i, t_sekot *sekot)
{
	while (line[i] == '\'')
	{
		if (line[i + 1] && line[i + 1] != '\'')
			i++;
		while (line[i] && line[i] != '\'')
		{
			if (line[i] == ' ')
			{
				sekot->flagcs = 1;
				return (i);
			}
			i++;
		}
		i++;
	}
	while (line[i] && line[i] != '\'')
		i++;
	if (line[i] && line[i + 1] && (line[i + 1] &&
		(line[i + 1] == ' ' || line[i + 1] == '\0')))
	{
		sekot->flagcs = 1;
		return (i + 1);
	}
	return (i);
}

int	ft_checkifsimplequote2(char *line, int i, int a)
{
	a = i + 1;
	while (line[a] && line[a] != ' ' && line[a] != '\t' &&
		line[a] != '\'' && line[a] != '\'')
		a++;
	return (a);
}
