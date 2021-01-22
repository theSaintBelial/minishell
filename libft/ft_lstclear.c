/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgorilla <lgorilla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:03:14 by lgorilla          #+#    #+#             */
/*   Updated: 2020/05/20 12:40:10 by lgorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;
	t_list *nxt;

	if (!del)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		nxt = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = nxt;
	}
	*lst = NULL;
}
