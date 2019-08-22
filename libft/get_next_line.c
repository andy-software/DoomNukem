/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:07:25 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/07 17:07:28 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*this_strcdup(char *str, char c)
{
	int		i;
	char	*new_str;
	char	*head;

	i = 0;
	while (str[i] != c)
		i++;
	new_str = ft_strnew(i);
	if (!new_str)
		return (0);
	head = new_str;
	while (*str != c)
		*(new_str++) = *(str++);
	return (head);
}

static char	*this_strchr(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] != c)
		i++;
	new_str = ft_strdup(ft_strchr(str, c) + 1);
	ft_strdel(&str);
	return (new_str);
}

static int	make_it_shorter(char **line, char **lost)
{
	*line = this_strcdup(*lost, '\n');
	*lost = this_strchr(*lost, '\n');
	return (1);
}

static void	rejoin(char **lost, char *buff)
{
	char *link;

	link = *lost;
	*lost = ft_strjoin(*lost, buff);
	ft_strdel(&link);
}

int			get_next_line(const int fd, char **line)
{
	static char		*(lost[4864]);
	char			buff[BUFF_SIZE + 1];
	int				red_size;

	if (fd < 0 || fd > 4863 || read(fd, buff, 0) < 0)
		return (-1);
	if (!lost[fd])
		lost[fd] = ft_strnew(1);
	else if (ft_strchr(lost[fd], '\n'))
		return (make_it_shorter(line, &lost[fd]));
	while ((red_size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[red_size] = '\0';
		rejoin(&lost[fd], buff);
		if (ft_strchr(lost[fd], '\n'))
			return (make_it_shorter(line, &lost[fd]));
	}
	if (red_size == 0 && (!lost[fd] || *(lost[fd]) == 0))
		return (0);
	*line = ft_strdup(lost[fd]);
	ft_strdel(&(lost[fd]));
	return (1);
}
