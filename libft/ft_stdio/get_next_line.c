/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnovella <xfearlessrizzze@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 14:44:59 by lgorilla          #+#    #+#             */
/*   Updated: 2021/02/16 13:03:45 by lnovella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

#define BUFFER_SIZE 4096

static int		free_all(char **line, char **ost)
{
	if (*line)
		free(*line);
	if (*ost)
		free(*ost);
	return (1);
}

static int		del_join(char **line, char *buf, char **ost, int *flag)
{
	char	*ptr;
	char	*tmp;

	if ((ptr = ft_strchr(buf, '\n')))
	{
		*ptr = '\0';
		ptr++;
		if (((*ost = ft_strdup(ptr)) == NULL) && free_all(line, ost))
			return (-1);
		*flag = 1;
	}
	tmp = *line;
	if ((*line = ft_strjoin(*line, buf)) == NULL)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

static int		checker_line_ost(char **line, char **ost)
{
	char	*ptr;
	char	*tmp;

	if (*ost != NULL)
	{
		if ((ptr = ft_strchr(*ost, '\n')))
		{
			*ptr = '\0';
			*line = ft_strdup(*ost);
			tmp = *ost;
			*ost = ft_strdup(++ptr);
			free(tmp);
			if ((!(*line) || !(*ost)) && free_all(line, ost))
				return (-1);
			return (1);
		}
		*line = ft_strdup(*ost);
		free(*ost);
		*ost = NULL;
		if (!(*line))
			return (-1);
	}
	else if ((*line = ft_strdup("")) == NULL)
		return (-1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			res;
	static char	*ost;
	int			checker;
	int			flag;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if ((checker = checker_line_ost(line, &ost)) != 0)
		return (checker);
	flag = 0;
	while (!flag && (res = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[res] = '\0';
		if ((del_join(line, buf, &ost, &flag)) == -1)
			return (-1);
	}
	if (res < 0 && free_all(line, &ost))
		return (-1);
	return ((res || ost) ? 1 : 0);
}
