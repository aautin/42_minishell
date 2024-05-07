/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:31:19 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/07 17:47:22 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_freeall(char **arr_str)
{
	size_t	i;

	if (arr_str == NULL)
		return ;
	i = 0;
	while (arr_str[i] != NULL)
	{
		free(arr_str[i]);
		i++;
	}
	free(arr_str);
}
