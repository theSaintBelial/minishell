/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:37:00 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/01 19:56:01 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_ast_tree **root)
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
