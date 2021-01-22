/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svatostop <svatostop@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 12:14:14 by lgorilla          #+#    #+#             */
/*   Updated: 2020/10/24 19:03:25 by svatostop        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1024

# include <unistd.h>
# include <stdlib.h>

char	*ft_strchr(const char *str, int ch);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);
int		checker_line_ost(char **line, char **ost);
int		del_join(char **line, char *buf, char **ost, int *flag);
int		free_all(char **line, char **ost);

#endif
