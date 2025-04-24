/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:01:28 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/24 18:05:01 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned(va_list *args)
{
	unsigned int	nb;
	int				len;

	nb = va_arg(*args, unsigned int);
	len = 0;
	ft_putnbr_base_fd(nb, "0123456789", 1);
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}
