/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:42:03 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:05:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(void const *s, int c, size_t n)
{
	unsigned char const	*addr;
	unsigned char		byte;

	addr = (unsigned char const *)s;
	byte = (unsigned char)c;
	while (n--)
	{
		if (*addr == byte)
			return ((void *)(addr));
		addr++;
	}
	return (NULL);
}
