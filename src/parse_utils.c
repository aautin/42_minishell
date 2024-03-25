/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:42:35 by aautin            #+#    #+#             */
/*   Updated: 2024/03/20 18:44:53 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "parser.h"

int	nbr_len(unsigned char nbr)
{
	int	size;

	size = 1;
	while (nbr / 10)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

void	nbr_data(char **data, unsigned char nbr, int nbr_len)
{
	int	power;

	power = 1;
	while (nbr / power > 9)
		power *= 10;
	while (nbr_len--)
	{
		*((*data)++) = ((nbr / power) % 10) + '0';
		power = power / 10;
	}
}

int	change_quote_mode(char data, int *mode)
{
	if (data == '"' && *mode != SG_QUOTE)
	{
		if (*mode == NO_QUOTE)
		*mode = DB_QUOTE;
		else if (*mode == DB_QUOTE)
			*mode = NO_QUOTE;
		return (1);
	}
	else if (data == '\'' && *mode != DB_QUOTE)
	{
		if (*mode == NO_QUOTE)
			*mode = SG_QUOTE;
		else if (*mode == SG_QUOTE)
			*mode = NO_QUOTE;
		return (1);
	}
	return (0);
}

int	pathname_len(char *pathname)
{
	int	len;

	len = 0;
	if (!ft_isalpha(*pathname) && *pathname != '_')
		return (-1);
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	return (len);
}
