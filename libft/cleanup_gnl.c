/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:02:48 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 06:03:46 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cleanup_gnl_buffer(int fd)
{
	static char	*buffer[4096];

	if (fd >= 0 && fd < 4096 && buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
}
