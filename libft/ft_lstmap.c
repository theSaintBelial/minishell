/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:39:32 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/23 15:37:00 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_lst;
	t_list *new_lst_start;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	if (!(new_lst = ft_lstnew(f(lst->content))))
		return (NULL);
	new_lst_start = new_lst;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(tmp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		new_lst->next = tmp;
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (new_lst_start);
}
