/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:42:23 by rlucio-l          #+#    #+#             */
/*   Updated: 2021/09/30 18:29:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** NAME
** 		strlcat -- size-bounded string concatenation
** DESCRIPTION
** 		strlcat() appends string src to the end of dst.  It will append at most
** 		dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate,
** 		unless dstsize is 0 or the original dst string was longer than dstsize
** 		(in practice this should not happen as it means that either dstsize is
** 		incorrect or that dst is not a proper string).
** 		If the src and dst strings overlap, the behavior is undefined.
** RETURN VALUES
** 		strlcat() returns the total length of the string it tried to create.
** 		That means the initial length of dst plus the length of src.
*/

static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*destination;
	const char	*source;
	size_t		size;
	size_t		dst_len;

	destination = dst;
	source = src;
	size = dstsize;
	while (size-- && *destination != '\0')
		destination++;
	dst_len = destination - dst;
	size = dstsize - dst_len;
	if (size == 0)
		return (dst_len + ft_strlen(source));
	while (size-- > 1 && *source != '\0')
		*destination++ = *source++;
	*destination = '\0';
	while (*source++)
		;
	return (dst_len + (source - src) - 1);
}

/*
** NAME
** 		ft_strjoin -- concatenate two strings
** DESCRIPTION
** 		Allocates (with malloc(3)) and returns a new string,
** 		which is the result of the concatenation of ’s1’ and ’s2’.
** RETURN VALUE
** 		The new string. NULL if the allocation fails.
*/

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	str_size;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_size = s1_len + s2_len + 1;
	str = (char *) malloc(str_size * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str, s2, str_size);
	return (str);
}

/*
** NAME
** 		get_line - get a line from buffer
** DESCRIPTION
** 		Uses ft_strchr to locate a newline character
** 		on buffer
** RETURN VALUE
** 		On success, returns a string containing
** 		the first line found on buffer
** 		If there is no newline character or else,
** 		returns NULL
*/

static char	*get_line(char **static_buffer)
{
	char	*ptr_to_newline_char;
	size_t	line_size;
	char	*line;
	char	*temp_buffer;

	if (*static_buffer == NULL)
		return (NULL);
	ptr_to_newline_char = ft_strchr(*static_buffer, '\n');
	if (ptr_to_newline_char)
	{
		line_size = (ptr_to_newline_char - *static_buffer) + 1;
		line = ft_substr(*static_buffer, 0, line_size);
		ptr_to_newline_char++;
		temp_buffer = ft_strdup(ptr_to_newline_char);
		free(*static_buffer);
		*static_buffer = ft_strdup(temp_buffer);
		free(temp_buffer);
		return (line);
	}
	else
		return (NULL);
}

/*
** NAME
** 		assign_line - assign a string to the static variable line
** DESCRIPTION
** 		Receive bytes read from a previous call to read on file descriptor,
** 		and the addresses of the static variables static_buffer, buffer
** 		and line, which were initialized in get_next_line.
**
** 		If read was successfully called, join buffer to static_buffer,
** 		call get_line to check if there is a line on the string created.
** 		If a line was found, assign it to static variable line.
**
** 		If read returned EOF, and there is a string stored on static_buffer,
** 		assign it to line and set static_buffer to NULL.
*/

static void	assign_line(size_t bytes, char **sta_buf, char **buf, char **line)
{
	char	*temp;

	if (bytes > 0)
	{
		if (*sta_buf == NULL)
			*sta_buf = ft_strdup("");
		temp = ft_strjoin(*sta_buf, *buf);
		free(*sta_buf);
		*sta_buf = ft_strdup(temp);
		free(temp);
		*line = get_line(sta_buf);
	}
	free(*buf);
	if (bytes <= 0 && *sta_buf != NULL)
	{
		*line = ft_strdup(*sta_buf);
		free(*sta_buf);
		*sta_buf = NULL;
	}
}

/*
** NAME
** 		get_next_line
** DESCRIPTION
** 		A function which returns a line read from a
** 		file descriptor
** RETURN VALUE
** 		Read line: correct behavior
** 		NULL: nothing else to read or an error occurred
*/

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*static_buffer;
	char			*line;
	size_t			bytes_read;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(&static_buffer);
	while (line == NULL)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		assign_line(bytes_read, &static_buffer, &buffer, &line);
		if (bytes_read <= 0 && static_buffer == NULL)
			break ;
	}
	return (line);
}
