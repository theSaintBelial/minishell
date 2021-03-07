/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thesaintbelial <thesaintbelial@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:19:31 by lnovella          #+#    #+#             */
/*   Updated: 2021/03/07 09:32:59 by thesaintbel      ###   ########.fr       */
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
bool				env_lst_delone(t_env **env, char *name);
void				env_lst_sort(t_env *env);
t_env				*env_lst_find(t_env *envlst, char *data_ref);
t_env				*env_lst_new(char *name, char *value, bool visible);
t_env				*env_lst_dup(t_env *envlst);
void				env_lst_clear(t_env *env);
char				**env_lst_tostrarr(t_env *envlst, bool visible);
char				*env_lst_node_to_str(t_env *envlst);
size_t				env_lst_len(t_env *env, bool visible);
char				*env_lst_getval(t_env *envlst, char *name);
void				env_lst_set(t_env *envlst, char *set, bool visible);
void 				print_env_lst(t_env *envlst, bool visible);

#endif
