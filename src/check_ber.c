/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ber.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:10:59 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/28 20:11:37 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber(char *map_name)
{
	int	len;

	len = ft_strlen(map_name);
	return (len > 4 && !ft_strncmp(map_name + len - 4, ".ber", 4));
}
