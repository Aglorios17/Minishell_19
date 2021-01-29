#include "../include/minishell.h"

char **ft_tabreturn(t_list *list)
{
	t_list *tmp;
	char **tab;
	int i;
	
	tab = NULL;
	i = 0;
	tmp = list;
	if ((tab = malloc(sizeof(char *) * (ft_lstsize(list) + 1))) == NULL)
		return (0);
	while (list)
	{
		tab[i] = ft_strdup((char *)list->content);
		i++;
		list = list->next;
	}
	tab[i] = NULL;
	list = tmp;
	return (tab);
}
