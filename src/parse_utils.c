/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:42:35 by aautin            #+#    #+#             */
/*   Updated: 2024/05/15 17:20:27 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "parser.h"

size_t	nbr_len(unsigned char nbr)
{
	size_t	size;

	if (nbr == 0)
		return (1);
	size = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

void	nbr_data(char *data[], unsigned char nbr)
{
	size_t	power;
	size_t	len;

	len = nbr_len(nbr);
	power = 1;
	while (nbr / power > 9)
		power *= 10;
	while (len--)
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

size_t	pathname_len(char const pathname[])
{
	size_t	len;

	len = 0;
	if (!ft_isalpha(pathname[0]) && pathname[0] != '_')
		return (0);
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	return (len);
}
