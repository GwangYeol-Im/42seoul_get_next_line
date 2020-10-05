/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gim <gim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 22:03:58 by gim               #+#    #+#             */
/*   Updated: 2020/10/05 22:22:43 by gim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_get_line(char **backup, char **line)
{
	int				idx;
	char			*temp;
	char			*split;
	
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

int					ft_read_file(int fd, char **line, char *buffer, char **backup)
{
	int				re;

	while ((re = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (!*backup)
			*backup = ft_strdup(buffer);
		else
			*backup = ft_strjoin(*backup, buffer);
		if (ft_get_line(backup, line))
			break ;
	}
	return (re > 0 ? 1 : 0);
}

int					get_next_line(int fd, char **line)
{
	static char		*backups[FD_MAX];
	char			*buffer;
	int				idx;
	int				re;

	if (!line || (fd < 0 || fd > FD_MAX) || (read(fd, backups[fd], 0) < 0) \
		|| !(buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	if (backups[fd])
		if (ft_get_line(&backups[fd], line))
			return (1);
	idx = 0;
	while (idx <= BUFFER_SIZE)
		buffer[idx++] = '\0';
	re = ft_read_file(fd, line, buffer, &backups[fd]);
	free(buffer);
	if (re != 0 || backups[fd] == NULL || backups[fd][0] == '\0')
	{
		if (!re && *line)
			*line = NULL;
		return (re);
	}
	*line = backups[fd];
	backups[fd] = NULL;
	return (1);
}
