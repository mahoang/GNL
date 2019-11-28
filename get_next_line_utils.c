/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:02:24 by mahoang           #+#    #+#             */
/*   Updated: 2019/11/26 18:13:12 by mahoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int c;

	if (!str)
		return (0);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	int			i;
	int			j;
	int			size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(s3 = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
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

	if (!src)
		return (NULL);
	ssrc = (char*)src;
	if (!(dest = malloc(sizeof(*src) * ft_strlen(src) + 1)))
		return (NULL);
	ft_strcpy(dest, ssrc);
	return (dest);
}
