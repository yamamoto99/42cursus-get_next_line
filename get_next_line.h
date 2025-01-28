/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masayama <masayama@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:41:13 by masayama          #+#    #+#             */
/*   Updated: 2025/01/28 22:32:20 by masayama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif
# define GNL_READ_ERROR -2
# define GNL_REALLOC_ERROR -3
# define GNL_PUSH_CHAR_ERROR -4

typedef struct gnl_buffer
{
	char	*data;
	size_t	length;
	size_t	capacity;
}			t_gnl_buffer;

void		ft_init_buffer(t_gnl_buffer *buffer);
int			ft_get_char(int fd);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_expand_buffer(t_gnl_buffer *buffer, size_t new_capacity);
int			ft_push_char(t_gnl_buffer *buffer, unsigned char c);
char		*get_next_line(int fd);

#endif
