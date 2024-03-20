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
	if (!ft_isalpha(pathname[len]))
		return (-1);
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	return (len);
}
