/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/03/18 14:57:35 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "expansion.h"

void	parse_quotes(char *content)
{
	char	mode;

	mode = NO_QUOTE;
	while (*content)
	{
		if (*content == '\'' && (mode == NO_QUOTE || mode == SG_QUOTE))
		{
			if (mode == SG_QUOTE)
				mode = NO_QUOTE;
			else if (mode == NO_QUOTE)
				mode = SG_QUOTE;
			ft_memmove(content, content + 1, ft_strlen(content + 1) + 1);
		}
		else if (*content == '"' && (mode == NO_QUOTE || mode == DB_QUOTE))
		{
			if (mode == DB_QUOTE)
				mode = NO_QUOTE;
			else if (mode == NO_QUOTE)
				mode = DB_QUOTE;
			ft_memmove(content, content + 1, ft_strlen(content + 1) + 1);
		}
		else
			content++;
	}
}

static void	change_mode(char a, char *mode, int *i, int add_to_i)
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

static int	parse_data_len(char *data, int data_len)
{
	int		i;
	char	mode;

	mode = NO_QUOTE;
	i = 0;
	while (data[i])
	{
		if ((data[i] == '"' && mode != SG_QUOTE)
			|| (data[i] == '\'' && mode != DB_QUOTE))
			change_mode(data[i], &mode, &data_len, -1);
		else if (data[i] == '$' && mode != SG_QUOTE)
			data_len += expansion_len(&data[i + 1], &mode, &i);
		i++;
	}
	return (printf("%s: %d\n", data, data_len), data_len);
}

static void	parse_data(char *data, char *parsed_data)
{
	int		i;
	int		parsed_i;
	char	mode;

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

int	parse_token(t_token *token)
{
	int		len;
	char	*parsed_data;

	len = parse_data_len(token->data, ft_strlen(token->data));
	parsed_data = malloc((len + 1) * sizeof(char));
	if (parsed_data == NULL)
	{
		perror("parse_token():malloc()");
		return (1);
	}
	parse_data(token->data, parsed_data);
	free(token->data);
	token->data = parsed_data;
	return (0);
}
