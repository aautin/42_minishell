/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:12 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/22 15:44:00 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

char	*ft_strtrim(char const s1[], char const set[])
{
	char const	*start;

	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	start = s1;
	while (*s1 != '\0')
		s1++;
	s1--;
	while (start < s1 && ft_strchr(set, *s1) != NULL)
		s1--;
	s1++;
	return (ft_substr(start, 0, s1 - start));
}
