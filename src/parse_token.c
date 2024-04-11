/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/04/11 15:38:56 by aautin           ###   ########.fr       */
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

int	expansion(t_token *token, t_list *envp, int ignore_quotes, int exit_status)
{
	t_expansion const	config = {envp, exit_status, ignore_quotes};
	char				*expanded_data;
	int					expanded_len;

	expanded_len = expand_len(&config, token->data);
	expanded_data = ft_calloc(expanded_len + 1, sizeof(char));
	if (expanded_data == NULL)
	{
		perror("parse_token():malloc()");
		return (1);
	}
	expand_data(&config, token->data, expanded_data);
	free(token->data);
	token->data = expanded_data;
	return (0);
}

int	parse_token(t_token *token, t_list *envp, int exit_status)
{
	if (expansion(token, envp, 0, exit_status))
		return (1);
	unquote(token->data);
	return (0);
}
