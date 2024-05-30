/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/05/30 18:43:01 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "parser_utils.h"

#include "getenv.h"

int	unquote(char data[], int starting_mode)
{
	int	mode;

	mode = starting_mode;
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
	return (mode);
}

int	parse_token(t_token *token, t_list *envp, int exit_status,
	int ignore_quotes)
{
	t_expansion const	config = {envp, exit_status, ignore_quotes};
	t_list				*components;

	components = get_token_components(token->data);
	if (components == NULL)
		return (perror("get_token_components():ft_lstnew()"), 1);
	if (parse_components(&config, components) == 1)
	{
		perror("parse_token():malloc()");
		ft_lstclear(&components, free);
		return (1);
	}
	if (components_to_data(token, components) == 1)
	{
		perror("components_to_data():malloc()");
		return (1);
	}
	return (0);
}
