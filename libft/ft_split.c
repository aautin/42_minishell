/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:28:42 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/05 15:34:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static size_t	len_word(char const s[], char c)
{
	char const	*start;

	start = s;
	while (*s != c && *s != '\0')
		s++;
	return (s - start);
}

char	**ft_split(char const s[], char c)
{
	char	**arr_str;
	size_t	num_words;
	size_t	len;
	size_t	i;

	num_words = ft_countwords(s, c);
	arr_str = malloc((num_words + 1) * sizeof(char *));
	if (arr_str == NULL)
		return (NULL);
	arr_str[num_words] = NULL;
	i = 0;
	while (i < num_words)
	{
		while (*s == c && *s != '\0')
			s++;
		len = len_word(s, c);
		arr_str[i] = ft_substr(s, 0, len);
		if (arr_str[i++] == NULL)
		{
			ft_freeall(arr_str);
			return (NULL);
		}
		s += len;
	}
	return (arr_str);
}
