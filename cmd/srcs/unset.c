#include "../../include/minishell.h"

int ft_unset(shell *st)
{
	t_list *tmp;
	t_list *previous;
	char *un;
	char *fri;

	tmp = NULL;
	previous = NULL;
	fri = NULL;
	un = ft_strdup((char *)st->tokens->content);
	if (!ft_strncmp(un, "PWD\0", ft_strlen(un)))
		st->pwd = ft_strdup("");
	if (!ft_strncmp(un, "PATH\0", ft_strlen(un)))
		st->pat = ft_strdup("");
	if (un[0] == '\0')
	{
		write(1, "minishell: unset: `", 19);
		write(1, "': not a valid identifier\n", 26);
		if (!ft_strchr(un, ' '))
			st->status = 1;
		free(un);
		return (0);
	}
	if (ft_strchr(un, '=') || ft_strchr(un, ' '))
	{
		write(1, "minishell: unset: `", 19);
		write(1, un, ft_strlen(un));
		write(1, "': not a valid identifier\n", 26);
		if (!ft_strchr(un, ' '))
			st->status = 1;
		free(un);
		return (0);
	}
	fri = un;
	un = ft_charjoin(un, '=');
	free(fri);
	previous = st->envv;
	if (!ft_strncmp(un, (char *)previous->content, ft_strlen(un)))
	{
		st->envv = previous->next;
		free(previous);
		st->firstenv = st->envv;
		free(un);
		return (0);
	}
	previous = st->envv;
	tmp = previous->next;
	while (tmp)
	{
		if (!ft_strncmp(un, (char *)tmp->content, ft_strlen(un)))
		{
			previous->next = tmp->next;
			free(tmp);
			st->envv = st->firstenv;
			free(un);
			return (0);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	st->envv = st->firstenv;
	free(un);
	return (0);
}
