/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrynevi <mhrynevi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:35:22 by mhrynevi          #+#    #+#             */
/*   Updated: 2024/04/10 20:01:19 by mhrynevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buf(int fd, char *buf, int *eof)
{
	int	read_num;

	read_num = -1;
	read_num = read (fd, buf, BUFFER_SIZE);
	if (read_num == -1)
		return (free(buf), NULL);
	buf[read_num] = '\0';
	if (read_num == 0)
	{
		buf[1] = '\0';
		*eof = 1;
	}
	return (buf);
}

char	*alloc_buf(int fd, char *buf, int *eof)
{
	char		*duplicate;
	char		*temp;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	duplicate = (char *)malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!duplicate)
		return (free (buf), NULL);
	duplicate = read_buf(fd, duplicate, eof);
	if (!duplicate)
		return (free (buf), free (duplicate), NULL);
	if (!buf)
		return (free (buf), duplicate);
	temp = ft_strjoin(buf, duplicate);
	if (!temp)
		return (free (duplicate), free (buf), NULL);
	return (free (duplicate), free (buf), temp);
}

char	*new_buf(char *buf, int count)
{
	char	*temp;

	if (buf[count + 1] != '\0')
	{
		temp = ft_strdup(buf + (count + 1));
		if (!temp)
			return (free (buf), NULL);
		return (free (buf), temp);
	}
	return (free(buf), NULL);
}

char	*get_next_line(int fd)
{
	static int		count;
	static char		*buf;
	char			*line;
	int				eof;

	eof = 0;
	buf = alloc_buf (fd, buf, &eof);
	if (!buf)
		return (free (buf), buf = NULL, NULL);
	while (buf[count] != '\0' && buf[count] != '\n')
		count++;
	if ((buf[count] == '\0' && count > 0) && !eof)
		return (get_next_line(fd));
	else if (buf[count] == '\n' || ((buf[count] == '\0' && count > 0) && eof))
	{
		line = ft_substr(buf, 0, count + 1);
		if (!line)
			return (free (buf), buf = NULL, NULL);
		if (buf[count] == '\0')
			return (free (buf), buf = NULL, count = 0, line);
		else
			buf = new_buf(buf, count);
		return (count = 0, line);
	}
	return (free (buf), buf = NULL, NULL);
}
#include <stdio.h>
int main()
{
	int fd;
	int	i = 2;
	char *res;

	fd = open("/home/mrk/Documents/Work/42/get_next_line/empty.txt", O_RDONLY);
	while (i > 0)
	{
		res = get_next_line(fd);
		printf ("%s", res);
		free (res);
		res = NULL;
		i--;
	}
	close (fd);
}