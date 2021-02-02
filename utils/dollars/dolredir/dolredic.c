/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolredic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_init_retok(t_retok *retok, char *tmp, int i)
{
	retok->new = ft_strdup("");
	retok->tmp2 = tmp;
	retok->env = NULL;
	retok->first = ft_strdup("");
	retok->after = NULL;
	retok->adol = 0;
	retok->a = 0;
	retok->count = i;
}

void	ft_dolredir4(t_retok *retok, t_shell *st, char *tmp)
{
	char	*fri;

	fri = NULL;
	retok->count++;
	while (tmp[retok->count] && !ft_strchr("\'\"", tmp[retok->count])
		&& tmp[retok->count] != '\0')
	{
		if (!ft_isalnum(tmp[retok->count]) && tmp[retok->count] != '_'
			&& tmp[retok->count] != '?')
			break ;
		if (tmp[retok->count] == '$' || tmp[retok->count] == '\\')
			break ;
		fri = retok->new;
		retok->new = ft_charjoin(retok->new, tmp[retok->count]);
		free(fri);
		retok->count++;
	}
	retok->after = ft_strdup(&tmp[retok->count]);
	st->pass = retok->count - 1;
	fri = retok->new;
	retok->new = ft_charjoin(retok->new, '=');
	free(fri);
}

int		ft_dolredir3(t_retok *retok, t_shell *st, char *tmp)
{
	char	*fri;

	fri = NULL;
	if (tmp[retok->count + 1] == '\0' || tmp[retok->count + 1] == '\\')
	{
		if (retok->first[0] != '\0')
		{
			free(st->tmpq);
			st->tmpq = ft_strjoin(retok->first, "$");
		}
		else
		{
			fri = st->tmpq;
			st->tmpq = ft_charjoin(st->tmpq, '$');
			free(fri);
		}
		st->pass = retok->count;
		return (0);
	}
	return (1);
}

void	ft_dolredir2(t_retok *retok, char *tmp)
{
	char *fri;

	fri = NULL;
	while (tmp[retok->a] && retok->a < retok->count)
	{
		fri = retok->first;
		retok->first = ft_charjoin(retok->first, tmp[retok->a]);
		free(fri);
		retok->a++;
	}
}

int		ft_dolredic(t_shell *st, char *tmp, int i)
{
	t_retok	retok;

	st->pass = 0;
	ft_init_retok(&retok, tmp, i);
	ft_dolredir2(&retok, tmp);
	if (ft_dolredir3(&retok, st, tmp) == 0)
		return (0);
	ft_dolredir4(&retok, st, tmp);
	ft_dolredir5(&retok, st);
	ft_dolredir6(&retok, st, tmp);
	free(retok.after);
	free(retok.env);
	free(retok.new);
	free(retok.first);
	return (1);
}
