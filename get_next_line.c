/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucio-l <rlucio-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:42:23 by rlucio-l          #+#    #+#             */
/*   Updated: 2021/09/28 20:25:34 by rlucio-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*getline(char **static_buffer)
{

}

/*
** NAME
** 		get_next_line
** DESCRIPTION
** 		Write a function which returns a line read from a
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
