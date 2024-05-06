/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrynevi <mhrynevi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:17 by mhrynevi          #+#    #+#             */
/*   Updated: 2024/04/10 20:01:20 by mhrynevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*buf;
	int		count;
	int		i;

	i = 0;
	count = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	buf = (char *)malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (NULL);
	while (s1[i])
	{
		buf[i] = s1[i];
		i++;
	}
	while (s2[count] && i < size)
	{
		buf[i] = s2[count];
		i++;
		count++;
	}
	buf[i] = '\0';
	return (buf);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc(((ft_strlen((char *)s)) + 1) * sizeof(char));
	i = 0;
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = (char) s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	p;
	unsigned int	c;
	char			*sub;

	c = 0;
	p = start;
	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s))
		len = 0;
	else if (len > (ft_strlen((char *)s) - start))
		len = ft_strlen((char *)s) - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (*s && len--)
	{
		sub[c] = s[p];
		c++;
		p++;
	}
	sub[c] = '\0';
	return (sub);
}
