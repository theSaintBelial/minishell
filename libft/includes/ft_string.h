/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:52:39 by lnovella          #+#    #+#             */
/*   Updated: 2021/02/16 13:17:33 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdlib.h>

void				ft_bzero(void *str, size_t n);
void				*ft_memccpy(void *dst, const void *str, int c, size_t n);
void				*ft_memchr(const void *src, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *dst, const void *str, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *str, int c, size_t n);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *str, int ch);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strnstr(const char *big, const char *little, size_t n);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

#endif
