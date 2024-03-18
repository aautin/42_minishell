/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/03/18 14:50:50 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "expansion.h"

static void	change_mode(char a, char *mode, unsigned int *i, int add_to_i)
{
	if (a == '"' && *mode != SG_QUOTE)
	{
		if (*mode == NO_QUOTE)
			*mode = DB_QUOTE;
		else if (*mode == DB_QUOTE)
			*mode = NO_QUOTE;
		*i += add_to_i;
	}
	else if (a == '\'' && *mode != DB_QUOTE)
	{
		if (*mode == NO_QUOTE)
			*mode = SG_QUOTE;
		else if (*mode == SG_QUOTE)
			*mode = NO_QUOTE;
		*i += add_to_i;
	}
}

static void	parse_data(char *data, char *parsed_data)
{
	unsigned int	i;
	unsigned int	parsed_i;
	char			mode;

	mode = NO_QUOTE;
	i = 0;
	parsed_i = 0;
	while (data[i])
	{
		if ((data[i] == '"' && mode != SG_QUOTE)
			|| (data[i] == '\'' && mode != DB_QUOTE))
			change_mode(data[i], &mode, &i, 1);
		else if (data[i] == '$' && mode != SG_QUOTE)
			i += expansion(&data[i + 1], parsed_data, &mode, &parsed_i);
		else
		{
			parsed_data[parsed_i] = data[i];
			i++;
			parsed_i++;
		}
	}
	parsed_data[parsed_i] = '\0';
	printf("%s\n", parsed_data);
}

static int	parse_data_len(char *data, int data_len)
{
	unsigned int	i;
	char			mode;

	mode = NO_QUOTE;
	i = 0;
	while (data[i])
	{
		if ((data[i] == '"' && mode != SG_QUOTE)
			|| (data[i] == '\'' && mode != DB_QUOTE))
			change_mode(data[i], &mode, (unsigned int *) &data_len, -1);
		else if (data[i] == '$' && mode != SG_QUOTE)
			data_len += expansion_len(&data[i + 1], &mode, &i);
		i++;
	}
	return (printf("%s: %d\n", data, data_len), data_len);
}

static int	parse_token(t_token *token)
{
	unsigned int	len;
	char			*parsed_data;

	len = parse_data_len(token->data, ft_strlen(token->data));
	parsed_data = malloc((len + 1) * sizeof(char));
	if (parsed_data == NULL)
		return (1);
	parse_data(token->data, parsed_data);
	free(token->data);
	token->data = parsed_data;
	return (0);
}

int	parse_tokens(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = (t_token *) tokens->content;
		if ((token->type & T_WORD) == 1)
		{
			if (parse_token(token) == 1)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
