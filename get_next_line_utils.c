/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masayama <masayama@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:04:03 by masayama          #+#    #+#             */
/*   Updated: 2025/01/28 22:28:53 by masayama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_init_buffer(t_gnl_buffer *buffer)
{
	buffer->data = NULL;
	buffer->length = 0;
	buffer->capacity = 0;
}

int	ft_get_char(int fd)
{
	static unsigned char	buffer[BUFFER_SIZE];
	static unsigned char	*buffer_ptr = buffer;
	static int				buffer_remaining = 0;
	ssize_t					read_bytes;

	if (buffer_remaining == 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (GNL_READ_ERROR);
		if (read_bytes == 0)
			return (EOF);
		buffer_ptr = buffer;
		buffer_remaining = read_bytes;
	}
	buffer_remaining--;
	return ((int)*buffer_ptr++);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

int	ft_realloc_buffer(t_gnl_buffer *buffer, size_t new_capacity)
{
	char	*new_data;

	new_data = (char *)malloc(new_capacity);
	if (!new_data)
		return (GNL_REALLOC_ERROR);
	if (buffer->data)
	{
		ft_memcpy(new_data, buffer->data, buffer->length);
		free(buffer->data);
	}
	buffer->data = new_data;
	buffer->capacity = new_capacity;
	return (0);
}

int	ft_push_char(t_gnl_buffer *buffer, unsigned char c)
{
	if (buffer->length + 1 >= buffer->capacity)
	{
		if (buffer->capacity == 0)
			buffer->capacity = BUFFER_SIZE;
		else
			buffer->capacity *= 2;
		if (ft_realloc_buffer(buffer, buffer->capacity) == GNL_REALLOC_ERROR)
			return (GNL_PUSH_CHAR_ERROR);
	}
	buffer->data[buffer->length++] = (char)c;
	return (0);
}
