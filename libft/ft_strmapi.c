/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:05:00 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:55:51 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strmapi(char const s[], char (*f)(unsigned int, char))
{
	char	*dest;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[len] = '\0';
	i = 0;
	while (i < len)
	{
		*dest = f(i, *s);
		dest++;
		i++;
		s++;
	}
	return (dest - i);
}
