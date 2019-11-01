/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:02:24 by mahoang           #+#    #+#             */
/*   Updated: 2019/10/31 16:33:10 by mahoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t c;

	c = 0;
	while (src[c])
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int c;
	int d;

	c = 0;
	d = 0;
	while (dest[c])
		c++;
	while (src[d])
	{
		dest[c] = src[d];
		c++;
		d++;
	}
	dest[c] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s3;
	size_t			c;

	c = 0;
	if ((s1 == NULL && s2 == NULL) || !(s1 && s2))
		return (NULL);
	c = ft_strlen(s1) + ft_strlen(s2);
	if (!(s3 = malloc(sizeof(*s3) * (c + 1))))
		return (NULL);
	ft_strcpy(s3, s1);
	ft_strcat(s3, s2);
	return (s3);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s_new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= (size_t)ft_strlen(s))
	{
		len = 0;
		start = 0;
	}
	if (!(s_new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len-- && s[start])
		s_new[i++] = s[start++];
	s_new[i] = '\0';
	return (s_new);
}

char	*ft_strdup(const char *src)
{
	char *dest;
	char *ssrc;

	ssrc = (char*)src;
	if (!(dest = malloc(sizeof(*src) * ft_strlen(src) + 1)))
		return (NULL);
	ft_strcpy(dest, ssrc);
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
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
