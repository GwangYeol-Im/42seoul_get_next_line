/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gim <gim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 23:29:47 by gim               #+#    #+#             */
/*   Updated: 2020/10/11 17:39:10 by gim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	temp[idx] = '\0';
	split = ft_strdup(&temp[idx + 1]);
	*line = ft_strdup(*backup);
	free(*backup);
	*backup = split;
	return (1);
}

int				ft_read_file(int fd, char *buffer, char **line, char **backup)
{
	int			re;
	char		*temp;

	while ((re = read(fd, buffer, BS)) > 0)
	{
		if (!*backup)
			*backup = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(*backup, buffer);
			free(*backup);
			*backup = temp;
		}
		if (ft_get_line(backup, line))
			return (1);
		ft_memset(buffer, 0, BS + 1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*backups[FD_MAX];
	static char	*buffer;
	int			re;

	if (!line || (fd < 0 || fd > FD_MAX) || (read(fd, backups[fd], 0) < 0) \
	|| (BS <= 0) || !(buffer = malloc(sizeof(char) * (BS + 1))))
		return (-1);
	if (backups[fd])
		if (ft_get_line(&backups[fd], line))
			return (1);
	ft_memset(buffer, 0, BS + 1);
	re = ft_read_file(fd, buffer, line, &backups[fd]);
	free(buffer);
	if (!re)
	{
		if (backups[fd])
		{
			*line = ft_strdup(backups[fd]);
			free(backups[fd]);
			backups[fd] = NULL;
		}
		else
			*line = ft_strdup("");
	}
	return (re);
}
