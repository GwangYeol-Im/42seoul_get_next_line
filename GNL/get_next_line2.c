/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gim <gim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 23:29:47 by gim               #+#    #+#             */
/*   Updated: 2020/10/05 23:39:42 by gim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				get_next_line(int fd, char **line)
{
	static char	*backups[FD_MAX];
	char		*buffer;
	int			idx;
	int			re;

	if (!line || (fd < 0 || fd > FD_MAX) || (read(fd, backups[fd], 0) < 0) \
		|| !(buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	idx = 0;
	while (idx <= BUFFER_SIZE)
		buffer[idx++] = 0;
	re = ft_read_file(fd, line, buffer, &backups[fd]);
}