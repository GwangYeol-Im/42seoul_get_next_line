/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gim <gim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 22:04:02 by gim               #+#    #+#             */
/*   Updated: 2020/10/07 13:05:39 by gim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char		*ft_strdup(const char *s1)
{
	int		len;
	int		idx;
	char	*dest;

	len = ft_strlen(s1);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	idx = 0;
	while (idx <= len)
	{
		dest[idx] = s1[idx];
		idx++;
	}
	return (dest);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		idx;
	char	*new_s1;
	char	*new_s2;
	char	*join;

	new_s1 = (char *)s1;
	new_s2 = (char *)s2;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (0);
	idx = 0;
	while (*s1)
		join[idx++] = *s1++;
	while (*s2)
		join[idx++] = *s2++;
	join[idx] = '\0';
	return (join);
}

void		*ft_memset(void *ptr, int value, size_t num)
{
	char	*temp;

	temp = ptr;
	while (num--)
	{
		*temp++ = (char)value;
	}
	return (ptr);
}
