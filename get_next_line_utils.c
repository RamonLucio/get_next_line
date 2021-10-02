/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucio-l <rlucio-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:02:13 by rlucio-l          #+#    #+#             */
/*   Updated: 2021/10/02 17:45:08 by rlucio-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** NAME
** 		strchr -- locate character in string
** DESCRIPTION
** 		The strchr() function locates the first occurrence of c (converted
** 		to a char) in the string pointed to by s.  The terminating null
** 		character is considered to be part of the string; therefore if c is
** 		`\0', the functions locate the terminating `\0'.
** RETURN VALUES
** 		The function strchr() returns a pointer to the located character,
** 		or NULL if the character does not appear in the
** 		string.
*/

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

/*
** NAME
** 		strlen -- find length of string
** DESCRIPTION
** 		The strlen() function computes the length of the string s.
** RETURN VALUES
** 		The strlen() function returns the number of characters that precede
** 		the terminating NUL character.
*/

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p != '\0')
		p++;
	return (p - s);
}

/*
** NAME
** 		strlcpy -- size-bounded string copying
** DESCRIPTION
** 		strlcpy() copies up to dstsize - 1 characters from the string src to
** 		dst, NUL-terminating the result if dstsize is not 0.
** 		If the src and dst strings overlap, the behavior is undefined.
** RETURN VALUES
** 		strlcpy() returns the total length of the string it tried to create.
** 		That means the length of src.
*/

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

/*
** NAME
** 		strdup -- save a copy of a string
** DESCRIPTION
** 		The strdup() function allocates sufficient memory for a copy of the
** 		string s1, does the copy, and returns a pointer to it.  The pointer
** 		may subsequently be used as an argument to the function free(3).
** RETURN VALUE
** 		On  success, strdup() returns a pointer to the duplicated
** 		string. If insufficient memory is available, NULL is returned.
*/

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

/*
** NAME
** 		ft_substr -- returns a substring from the string ’s’
** DESCRIPTION
** 		Allocates (with malloc(3)) and returns a substring
** 		from the string ’s’.
** 		The substring begins at index ’start’ and is of
** 		maximum size ’len’.
** RETURN VALUE
** 		The substring. NULL if the allocation fails.
*/

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
