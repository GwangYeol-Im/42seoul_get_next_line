/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gim <gim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 23:29:47 by gim               #+#    #+#             */
/*   Updated: 2020/10/07 14:21:20 by gim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_get_line(char **backup, char **line)
{
	int			idx;
	char		*temp;
	char		*split;

	idx = 0;
	temp = *backup;
	while (temp[idx] != '\n')
	{
		if (!temp[idx++])
			return (0);
	}
	split = &temp[idx];
	*split = '\0';
	*line = ft_strdup(*backup);
	*backup = ft_strdup(split + 1);
	return (1);
}

int				ft_read_file(int fd, char *buffer, char **line, char **backup)
{
	int			re;

	while ((re = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (!*backup)
			*backup = ft_strdup(buffer);
		else
			*backup = ft_strjoin(*backup, buffer);
		if (ft_get_line(backup, line))
			return (1);
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*backups[FD_MAX];
	char		buffer[BUFFER_SIZE + 1];
	int			re;

	if (!line || (fd < 0 || fd > FD_MAX) || (read(fd, backups[fd], 0) < 0))
		return (-1);
	if (backups[fd])
		if (ft_get_line(&backups[fd], line))
			return (1);
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	re = ft_read_file(fd, buffer, line, &backups[fd]);
	if (!re && backups[fd])
	{
		*line = ft_strdup(backups[fd]);
		*backups[fd] = '\0';
	}
	return (re);
}
