/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:57:51 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 17:08:53 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *lst;

	lst = *alst;
	if (*alst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
	else
		*alst = new;
}
