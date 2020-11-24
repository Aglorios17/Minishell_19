/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:52:17 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 19:01:44 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *new;

	if (!lst)
		return (0);
	while (lst)
	{
		new = lst;
		lst = lst->next;
	}
	return (new);
}
