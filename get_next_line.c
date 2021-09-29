/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucio-l <rlucio-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:42:23 by rlucio-l          #+#    #+#             */
/*   Updated: 2021/09/29 09:59:37 by rlucio-l         ###   ########.fr       */
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
** 		retuns NULL
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
	static char		*static_buffer;
	static char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(&static_buffer);
}
