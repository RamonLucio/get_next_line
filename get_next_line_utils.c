/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucio-l <rlucio-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:02:13 by rlucio-l          #+#    #+#             */
/*   Updated: 2021/09/29 10:16:29 by rlucio-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	character;

	ptr = (char *) s;
	character = (char) c;
	while (*ptr)
	{
		if (*ptr == character)
			return (ptr);
		ptr++;
	}
	if (*ptr == character)
		return (ptr);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p != '\0')
		p++;
	return (p - s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*destination;
	const char	*source;
	size_t		destination_size;
	size_t		ch;

	destination = dst;
	source = src;
	destination_size = dstsize;
	if (destination_size != 0)
	{
		while (--destination_size)
		{
			ch = (*destination++ = *source++);
			if (ch == '\0')
				break ;
		}
	}
	if (destination_size == 0)
	{
		if (dstsize != 0)
			*destination = '\0';
		while (*source++)
			;
	}
	return (source - src - 1);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = (char *) malloc(len);
	if (ptr != NULL)
		ft_strlcpy(ptr, s1, len);
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	copied_chars;
	size_t	str_len;
	char	*substr;

	str_len = ft_strlen(s);
	if (str_len > start)
	{
		copied_chars = 0;
		while ((copied_chars < len) && ((start + copied_chars) < str_len))
			copied_chars++;
		substr = (char *) malloc((copied_chars + 1) * sizeof(char));
	}
	else
		return (ft_strdup(""));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, &s[start], copied_chars + 1);
	return (substr);
}
