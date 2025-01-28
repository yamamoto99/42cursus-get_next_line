/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masayama <masayama@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 00:39:08 by masayama          #+#    #+#             */
/*   Updated: 2025/01/28 22:28:23 by masayama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_gnl_buffer	line;
	int				c;

	if (fd < 0)
		return (NULL);
	ft_init_buffer(&line);
	while (1)
	{
		c = ft_get_char(fd);
		if (c == GNL_READ_ERROR)
			return (free(line.data), NULL);
		if (c == EOF)
			break ;
		if (ft_push_char(&line, (unsigned char)c) == GNL_PUSH_CHAR_ERROR)
			return (free(line.data), NULL);
		if (c == '\n')
			break ;
	}
	if (line.length > 0)
	{
		if (ft_push_char(&line, '\0') == GNL_PUSH_CHAR_ERROR)
			return (free(line.data), NULL);
		return (line.data);
	}
	return (free(line.data), NULL);
}
