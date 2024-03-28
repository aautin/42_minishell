/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:43:03 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/28 10:40:14 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "tokenize_utils.h"
#include "utils.h"

void	store_and_create_token(t_list **tokens, t_line_part *line_part)
{
	t_list	**last_node;

	if (*tokens == NULL)
		last_node = tokens;
	else
		last_node = &line_part->last_node;
	line_part->token->data = ft_substr(line_part->line, 0, line_part->index);
	if (add_to_list(last_node, line_part->token))
	{
		line_part->token = NULL;
		return ;
	}
	line_part->last_node = ft_lstlast(*last_node);
	line_part->token = malloc(sizeof(*line_part->token));
	if (line_part->token == NULL)
		perror("store_and_create_token():malloc()");
	line_part->token->type = T_NONE;
}

t_action	append_redirect_operator(t_line_part *line_part)
{
	char const	c = line_part->line[line_part->index];

	if (ft_strchr(REDIRECT_OPERATOR, c) == NULL)
		return (A_NONE);
	if (c == '>' && (line_part->token->type & T_REDIRECT_OUTPUT))
	{
		line_part->token->type &= ~T_REDIRECT_OUTPUT;
		line_part->token->type |= T_REDIRECT_APPEND;
		line_part->index++;
		return (A_CONTINUE);
	}
	if (c == '<' && (line_part->token->type & T_REDIRECT_INPUT))
	{
		line_part->token->type &= ~T_REDIRECT_INPUT;
		line_part->token->type |= T_REDIRECT_HERE_DOC;
		line_part->index++;
		return (A_CONTINUE);
	}
	return (A_NONE);
}

t_action	new_operator(t_list **tokens, t_line_part *line_part)
{
	char const	c = line_part->line[line_part->index];

	if (ft_strchr(OPERATOR_TOKENS, c) == NULL)
		return (A_NONE);
	if (line_part->token->type & T_WORD)
	{
		store_and_create_token(tokens, line_part);
		if (line_part->token == NULL)
			return (A_RETURN);
		line_part->line += line_part->index;
		line_part->index = 0;
	}
	line_part->token->type = T_OPERATOR;
	if (c == '>')
		line_part->token->type |= T_REDIRECT_OPERATOR | T_REDIRECT_OUTPUT;
	else if (c == '<')
		line_part->token->type |= T_REDIRECT_OPERATOR | T_REDIRECT_INPUT;
	else if (c == '|')
		line_part->token->type |= T_CONTROL_OPERATOR | T_PIPE;
	line_part->index++;
	return (A_CONTINUE);
}

t_action	ignore_blank(t_list **tokens, t_line_part *line_part)
{
	char const	c = line_part->line[line_part->index];

	if (!ft_isspace(c))
		return (A_NONE);
	if (line_part->token->type != T_NONE)
	{
		store_and_create_token(tokens, line_part);
		if (line_part->token == NULL)
			return (A_RETURN);
		line_part->line += line_part->index + 1;
		line_part->index = 0;
	}
	else
		line_part->line++;
	line_part->token->type = T_NONE;
	return (A_CONTINUE);
}
