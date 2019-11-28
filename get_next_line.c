/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:44:45 by mahoang           #+#    #+#             */
/*   Updated: 2019/11/28 11:11:50 by mahoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

int			to_free(char **str, int type)
{
	free(*str);
	*str = NULL;
	return (type);
}

int			ft_readline(char **stock, int fd)
{
	char	*str;
	char	*tmp;
	int		c;

	if (!*stock)
		*stock = ft_strdup("");
	if (!(str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_strchr(*stock, '\n'))
	{
		if ((c = read(fd, str, BUFFER_SIZE)) == -1)
			return (to_free(&str, -1));
		if (c == 0)
			return (to_free(&str, 0));
		str[c] = '\0';
		tmp = *stock;
		*stock = ft_strjoin(*stock, str);
		free(tmp);
	}
	return (to_free(&str, 1));
}

size_t		ft_linelen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int			get_next_line(int fd, char **line)
{
	static char	*stock = NULL;
	char		*tmp;
	int			ret;

	if (fd <= -1 || line == NULL || BUFFER_SIZE < 1 || read(fd, stock, 0) == -1)
		return (-1);
	if ((ret = ft_readline(&stock, fd)) == -1)
		return (to_free(&stock, -1));
	else if (ret == 0)
	{
		*line = ft_strdup(stock);
		return (to_free(&stock, 0));
	}
	ret = ft_linelen(stock);
	*line = ft_substr(stock, 0, ret);
	tmp = stock;
	stock = ft_strdup(stock + ret + 1);
	return (to_free(&tmp, 1));
}
