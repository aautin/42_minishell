/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:39:17 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:29:26 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strjoin(char const s1[], char const s2[])
{
	char	*dest;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dest = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, len1 + 1);
	ft_strlcpy(dest + len1, s2, len2 + 1);
	return (dest);
}
