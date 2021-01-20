#include "../include/minishell.h"

t_list	*lst_addin(char **tab, t_list *list, int i)
{
	t_list	*new;
	t_list	*ret;
	int		a;

	a = 0;
	new = NULL;
	ret = NULL;
	while (tab[a])
	{
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(tab[a])));
		a++;
	}
	if (i != 0)
	{
		a = i;
		while (i)
		{
			ft_lstadd_back(&ret, ft_lstnew(ft_strdup((char *)list->content)));
			list = list->next;
			i--;
		}
		if (a > 1)
			list = list->next;
	}
	while (new)
	{
		ft_lstadd_back(&ret, ft_lstnew(ft_strdup((char *)new->content)));
		new = new->next;
	}
	while (list)
	{
		ft_lstadd_back(&ret, ft_lstnew(ft_strdup((char *)list->content)));
		list = list->next;
	}
//	while (ret)
//	{
//		printf("ret|%s|\n", (char *)ret->content);
//		ret = ret->next;
//	}
//	exit(1);
	return (ret);
}
