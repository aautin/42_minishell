/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:35:50 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:08:17 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	unsigned char		*a_dest;
	unsigned char const	*a_src;

	a_dest = (unsigned char *)dest;
	a_src = (unsigned char const *)src;
	while (n--)
	{
		*a_dest = *a_src;
		a_dest++;
		a_src++;
	}
	return (dest);
}
