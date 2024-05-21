/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:39:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/21 16:24:09 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "list_utils.h"
#include "parser.h"
#include "tokenize_utils.h"

t_action	rule_1(t_list **tokens, t_line_part *line_part)
{
	t_list		**last_node;
	char const	c = line_part->line[line_part->index];

	if (c != '\0')
		return (A_NONE);
	if (line_part->token->type == T_NONE)
	{
		free(line_part->token);
		line_part->token = NULL;
		return (A_BREAK);
	}
	line_part->token->data = ft_substr(line_part->line, 0, line_part->index);
	if (*tokens == NULL)
		last_node = tokens;
	else
		last_node = &line_part->last_node;
	if (line_part->token->data == NULL
		|| add_to_list(last_node, line_part->token))
		return (A_RETURN);
	line_part->token = NULL;
	return (A_BREAK);
}

t_action	rule_2_3(t_list **tokens, t_line_part *line_part)
{
	t_action	action;

	action = A_NONE;
	if (!(line_part->token->type & T_OPERATOR))
		return (A_NONE);
	if (line_part->token->type & T_REDIRECT_OPERATOR)
		action = append_redirect_operator(line_part);
	if (action != A_NONE)
		return (action);
	store_and_create_token(tokens, line_part);
	if (line_part->token == NULL)
		return (A_RETURN);
	line_part->line += line_part->index;
	line_part->index = 0;
	return (A_CONTINUE);
}

t_action	rule_4(t_line_part *line_part)
{
	char const	c = line_part->line[line_part->index];

	if (ft_strchr(QUOTE_CHARS, c) == NULL)
		return (A_NONE);
	if (c == '\'')
	{
		if (line_part->mode == NO_QUOTE)
			line_part->mode = SG_QUOTE;
		else if (line_part->mode == SG_QUOTE)
			line_part->mode = NO_QUOTE;
	}
	else if (c == '"')
	{
		if (line_part->mode == NO_QUOTE)
			line_part->mode = DB_QUOTE;
		else if (line_part->mode == DB_QUOTE)
			line_part->mode = NO_QUOTE;
	}
	line_part->token->type = T_WORD | T_QUOTED;
	line_part->index++;
	return (A_CONTINUE);
}

t_action	rule_6_7(t_list **tokens, t_line_part *line_part)
{
	t_action	action;

	if (line_part->mode != NO_QUOTE)
		return (A_NONE);
	action = new_operator(tokens, line_part);
	if (action != A_NONE)
		return (action);
	action = ignore_blank(tokens, line_part);
	return (action);
}

t_action	rule_8_9_10(t_line_part *line_part)
{
	char const	c = line_part->line[line_part->index];

	if (line_part->token->type & T_WORD)
	{
		line_part->index++;
		return (A_CONTINUE);
	}
	if (c == '#')
	{
		if (line_part->token->type == T_NONE)
		{
			free(line_part->token);
			line_part->token = NULL;
		}
		return (A_BREAK);
	}
	line_part->token->type = T_WORD;
	line_part->index++;
	return (A_CONTINUE);
}
