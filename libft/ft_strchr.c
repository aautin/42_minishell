/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:36:52 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:25:38 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(char const s[], int c)
{
	char	character;

	character = (char)c;
	while (*s != character)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
