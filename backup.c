# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
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

char	*ft_strjoin(char const *s1, char const *s2)
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

char	*get_line(char **buffer)
{
	char	*ptr_to_newline_char;
	size_t	line_size;
	char	*line;
	char	*temp_buffer;

	if (*buffer == NULL)
		return (NULL);
	ptr_to_newline_char = ft_strchr(*buffer, '\n');
	if (ptr_to_newline_char)
	{
		line_size = (ptr_to_newline_char - *buffer) + 1;
		line = ft_substr(*buffer, 0, line_size);
		ptr_to_newline_char++;
		temp_buffer = ft_strdup(ptr_to_newline_char);
		free(*buffer);
		*buffer = ft_strdup(temp_buffer);
		free(temp_buffer);
		return (line);
	}
	else
		return (NULL);
}

void	assign_line(size_t bytes, char **sta_buf, char **buffer, char **line)
{
	char	*temp;

	if (bytes > 0)
	{
		if (*sta_buf == NULL)
			*sta_buf = ft_strdup("");
		temp = ft_strjoin(*sta_buf, *buffer);
		free(*sta_buf);
		*sta_buf = ft_strdup(temp);
		free(temp);
		*line = get_line(sta_buf);
	}
	free(*buffer);
	if (bytes <= 0 && *sta_buf != NULL)
	{
		*line = ft_strdup(*sta_buf);
		free(*sta_buf);
		*sta_buf = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char			*buffer;
	static char		*static_buffer;
	static char			*line;
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
		auxilary(bytes_read, &static_buffer, &buffer, &line);
		if (bytes_read <= 0 && static_buffer != NULL)
			break;
		if (bytes_read <= 0 && static_buffer == NULL)
			break ;
	}
	return (line);
}

int main(void)
{
	char	*temp;
	int	fd;

	fd = open("myfile.txt", O_RDONLY);

	while(1)
	{
		temp = get_next_line(fd);
		if (!temp)
		break ;
		printf("%s", temp);
		free(temp);
	}
	return (0);
}
