/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/03/19 20:26:24 by aautin           ###   ########.fr       */
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

static void	change_mode(char **data, char *mode)
{
	if (**data == '"' && *mode != SG_QUOTE)
	{
		if (*mode == NO_QUOTE)
			*mode = DB_QUOTE;
		else if (*mode == DB_QUOTE)
			*mode = NO_QUOTE;
	}
	else if (**data == '\'' && *mode != DB_QUOTE)
	{
		if (*mode == NO_QUOTE)
			*mode = SG_QUOTE;
		else if (*mode == SG_QUOTE)
			*mode = NO_QUOTE;
	}
	(*data)++;
}

static int	parse_len(char *data)
{
	char	mode;
	int		len;

	mode = NO_QUOTE;
	len = 0;
	while (*data)
	{
		if ((*data == '"' && mode != SG_QUOTE)
			|| (*data == '\'' && mode != DB_QUOTE))
			change_mode(&data, &mode);
		else if (*data == '$' && mode != SG_QUOTE)
			len += expansion_len(&data, &mode);
		else
		{
			data++;
			len++;
		}
	}
	return (len);
}

static void	parse(char *data, char *new_data)
{
	char	mode;

	mode = NO_QUOTE;
	while (*data)
	{
		if ((*data == '"' && mode != SG_QUOTE)
			|| (*data == '\'' && mode != DB_QUOTE))
			change_mode(&data, &mode);
		else if (*data == '$' && mode != SG_QUOTE)
			expansion(&data, &new_data, &mode);
		else
			*(new_data++) = *(data++);
	}
	*new_data = '\0';
}

int	parse_token(t_token *token)
{
	int		len;
	char	*new_data;

	len = parse_len(token->data);
	new_data = malloc((len + 1) * sizeof(char));
	if (new_data == NULL)
	{
		perror("parse_token():malloc()");
		return (1);
	}
	parse(token->data, new_data);
	printf("[%s] malloc's size:%d | new content:%s\n", token->data, len + 1, new_data);
	free(token->data);
	token->data = new_data;
	return (0);
}
