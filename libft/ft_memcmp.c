/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:01:00 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:06:55 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	unsigned char const	*addr1;
	unsigned char const	*addr2;

	if (n == 0)
		return (0);
	addr1 = (unsigned char const *)s1;
	addr2 = (unsigned char const *)s2;
	while (--n)
	{
		if (*addr1 != *addr2)
			break ;
		addr1++;
		addr2++;
	}
	return (*addr1 - *addr2);
}
