/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masayama <masayama@student.42tokyo.jp>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-26 03:37:56 by masayama          #+#    #+#             */
/*   Updated: 2025-01-26 03:37:56 by masayama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_init_buffer(t_gnl_buffer *buffer)
{
	buffer->data = NULL;
	buffer->length = 0;
	buffer->capacity = 0;
}

unsigned char	ft_get_char(int fd)
{
	static unsigned char	buffer[BUFFER_SIZE];
	static unsigned char	*buffer_ptr = buffer;
	static int				buffer_remaining = 0;
	int						read_bytes;

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
	return (*buffer_ptr++);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (const char *)src;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

int	ft_expand_buffer(t_gnl_buffer *buffer, size_t new_capacity)
{
	char	*new_data;

	new_data = (char *)malloc(new_capacity);
	if (!new_data)
		return (0);
	if (buffer->data)
	{
		ft_memcpy(new_data, buffer->data, buffer->length);
		free(buffer->data);
	}
	buffer->data = new_data;
	buffer->capacity = new_capacity;
	return (1);
}

int	ft_push_char(t_gnl_buffer *buffer, char c)
{
	if (buffer->length + 1 >= buffer->capacity)
	{
		if (buffer->capacity == 0)
			buffer->capacity = 128;
		else
			buffer->capacity *= 2;
		if (!ft_expand_buffer(buffer, buffer->capacity))
			return (0);
	}
	buffer->data[buffer->length++] = c;
	return (1);
}
