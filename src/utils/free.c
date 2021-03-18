/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:51:49 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/18 19:51:51 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

size_t				ast_len(t_ast_tree *root)
{
	t_ast_tree	*tmp;
	size_t		i;

	i = 0;
	if ((tmp = root))
		while (tmp)
		{
			i++;
			tmp = tmp->right;
		}
	return (i);
}

t_ast_tree			*free_nodes(t_ast_tree **left, t_ast_tree **right)
{
	free_tree(left);
	free_tree(right);
	return (NULL);
}

void				free_tree(t_ast_tree **root)
{
	if (root && *root)
	{
		free_tree(&(*root)->left);
		free_tree(&(*root)->right);
		if ((*root)->data)
			free((*root)->data);
		free(*root);
		*root = NULL;
	}
}

bool				ft_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (true);
}
