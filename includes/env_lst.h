/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:19:31 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/20 14:11:30 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LST_H
# define ENV_LST_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct 		s_env
{
	char			*name;
	char			*value;
	bool			visible;
	struct s_env	*next;
}					t_env;

void				env_lst_create(t_env **env, char **envp);
void				env_lst_add_back(t_env **lst, t_env *node);
void				env_lst_delone(t_env **env, char *name);
void				env_lst_sort(t_env *env);
t_env				*env_lst_find(t_env *envlst, char *data_ref);
t_env				*env_lst_new(char *name, char *value, bool visible);
t_env				*env_lst_dup(t_env *envlst);
void				env_lst_clear(t_env *env);

#endif
