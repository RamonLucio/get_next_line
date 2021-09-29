/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucio-l <rlucio-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:42:23 by rlucio-l          #+#    #+#             */
/*   Updated: 2021/09/29 10:40:25 by rlucio-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*get_line(char **buffer_remainder)
{
	char	*ptr_to_newline_char;
	size_t	line_size;
	char	*line;
	char	*temp_buffer;

	if (*buffer_remainder == NULL)
		return (NULL);
	ptr_to_newline_char = ft_strchr(*buffer_remainder, '\n');
	if (ptr_to_newline_char)
	{
		line_size = (ptr_to_newline_char - *buffer_remainder) + 1;
		line = ft_substr(*buffer_remainder, 0, line_size);
		ptr_to_newline_char++;
		temp_buffer = ft_strdup(ptr_to_newline_char);
		free(*buffer_remainder);
		*buffer_remainder = ft_strdup(temp_buffer);
		free(temp_buffer);
		return (line);
	}
	else
		return (NULL);
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
	static char		*buffer;
	static char		*buffer_remainder;
	static char		*line;
	size_t			bytes_read;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(&buffer_remainder);
	while (line == NULL)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
}
