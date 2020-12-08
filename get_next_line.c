/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imgwang-yeol <imgwang-yeol@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:12:55 by imgwang-yeo       #+#    #+#             */
/*   Updated: 2020/12/08 11:33:31 by imgwang-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlen(char *s)
{
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char			*ft_strdup(char *src)
{
	char		*dest;
	int			len;
	int			idx;

	if (!*src)
		return ("");
	len = ft_strlen(src) + 1;
	if (!(dest = (char *)malloc(sizeof(char) * len)))
		return (0);
	idx = 0;
	while (idx <= len)
	{
		dest[idx] = src[idx];
		idx++;
	}
	return (dest);
}

char			*ft_strjoin(char *s1, char *s2, int n)
{
	char		*join;
	int			len;
	int			idx;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(join = (char *)malloc(sizeof(char) * len)))
		return (0);
	idx = 0;
	while (*s1)
		join[idx++] = *s1++;
	while (*s2)
		join[idx++] = *s2++;
	join[idx] = '\0';
	if (n == 1 || n == 3)
		free(s1);
	if (n == 2 || n == 3)
		free(s2);
	return (join);
}

int				ft_get_line(char **backup, char **line)
{
	int			idx;
	char		*temp;
	char		*remain;

	idx = 0;
	temp = *backup;
	while (temp[idx] != '\n')
		if (!temp[idx++])
			return (0);
	temp[idx] = '\0';
	*line = ft_strdup(*backup);
	remain = ft_strdup(&temp[idx + 1]);
	free(*backup);
	*backup = remain;
	return (1);
}

int				get_next_line(char **line)
{
	static char *backup;
	char		buffer[BUFFER_SIZE];
	int			nread;

	if (ft_get_line(&backup, line))
		return (1);
	while ((nread = read(FD, buffer, BUFFER_SIZE)) != 0)
	{
		if (nread == -1)
			return (-1);
		buffer[nread] = '\0';
		if (!backup)
			backup = ft_strdup(buffer);
		else
			backup = ft_strjoin(backup, buffer, 1);
		if (ft_get_line(&backup, line))
			return (1);
	}
	*line = ft_strdup(backup);
	free(backup);
	return (0);
}