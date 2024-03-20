/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/03/20 18:49:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "parser_utils.h"

void	unquote(char data[])
{
	int	mode;

	mode = NO_QUOTE;
	while (*data)
	{
		if (*data == '\'' && (mode == NO_QUOTE || mode == SG_QUOTE))
		{
			if (mode == SG_QUOTE)
				mode = NO_QUOTE;
			else if (mode == NO_QUOTE)
				mode = SG_QUOTE;
			ft_memmove(data, data + 1, ft_strlen(data + 1) + 1);
		}
		else if (*data == '"' && (mode == NO_QUOTE || mode == DB_QUOTE))
		{
			if (mode == DB_QUOTE)
				mode = NO_QUOTE;
			else if (mode == NO_QUOTE)
				mode = DB_QUOTE;
			ft_memmove(data, data + 1, ft_strlen(data + 1) + 1);
		}
		else
			data++;
	}
}

int	parse_token(t_token *token)
{
	if (expansion(token))
		return (1);
	unquote(token->data);
	return (0);
}
