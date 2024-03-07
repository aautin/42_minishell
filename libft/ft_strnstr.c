/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:24 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:39:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

char	*ft_strnstr(char const big[], char const little[], size_t len)
{
	size_t	len_l;

	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	len_l = ft_strlen(little);
	while (*big != '\0')
	{
		if (len-- < len_l)
			break ;
		if (!ft_strncmp(big, little, len_l))
			return ((char *)big);
		big++;
	}
	return (NULL);
}
