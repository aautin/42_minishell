/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:50:08 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/16 19:57:31 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_basepos(char const base[], char c)
{
	char const	*found;

	if (c == '\0')
		return (-1);
	found = ft_strchr(base, c);
	if (found == NULL)
		return (-1);
	return (found - base);
}

int	ft_atoibase(char const str[], char const base[])
{
	int	sign;
	int	nb;
	int	len_base;
	int	i;

	sign = 1;
	nb = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0')
		return (0);
	len_base = ft_strlen(base);
	i = get_basepos(base, *(str++));
	while (i >= 0)
	{
		nb = nb * len_base + i;
		i = get_basepos(base, *(str++));
	}
	return (sign * nb);
}
