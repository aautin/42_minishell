/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/28 10:21:27 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "tokenize_rules.h"
#include "tokenize_utils.h"

static int		parse_line(t_list **tokens, t_line_part *line_part);
static t_list	*get_invalid_redirection_token(t_list *redirect);
static t_list	*get_invalid_control_token(t_list *control);

int	tokenize(t_list **tokens, char const line[])
{
	t_line_part	line_part;	

	line_part.token = malloc(sizeof(*line_part.token));
	if (line_part.token == NULL)
	{
		perror("tokenize():malloc()");
		return (2);
	}
	line_part.token->type = T_NONE;
	line_part.line = line;
	line_part.index = 0;
	line_part.mode = NO_QUOTE;
	return (parse_line(tokens, &line_part));
}

t_list	*verify_tokens(t_list *current_token)
{
	t_token	*token;
	t_list	*bad_node;

	token = current_token->content;
	if (token->type & T_CONTROL_OPERATOR)
		return (current_token);
	bad_node = NULL;
	while (current_token != NULL)
	{
		token = current_token->content;
		if (token->type & T_REDIRECT_OPERATOR)
			bad_node = get_invalid_redirection_token(current_token);
		else if (token->type & T_CONTROL_OPERATOR)
			bad_node = get_invalid_control_token(current_token);
		if (bad_node != NULL)
			return (bad_node);
		current_token = current_token->next;
	}
	return (NULL);
}

static int	parse_line(t_list **tokens, t_line_part *line_part)
{
	t_action	action;

	while (1)
	{
		action = rule_1(tokens, line_part);
		if (action == A_NONE)
			action = rule_2_3(tokens, line_part);
		if (action == A_NONE)
			action = rule_4(line_part);
		if (action == A_NONE)
			action = rule_6_7(tokens, line_part);
		if (action == A_NONE)
			action = rule_8_9_10(line_part);
		if (action == A_BREAK)
			break ;
		if (action == A_RETURN)
			return (2);
	}
	return (line_part->mode != NO_QUOTE);
}

static t_list	*get_invalid_redirection_token(t_list *redirect)
{
	t_token			*token;
	t_list *const	next_token = redirect->next;

	if (next_token == NULL)
		return (redirect);
	token = next_token->content;
	if (!(token->type & T_WORD))
		return (next_token);
	return (NULL);
}

static t_list	*get_invalid_control_token(t_list *control)
{
	t_token			*token;
	t_list *const	next_token = control->next;

	if (next_token == NULL)
		return (control);
	token = next_token->content;
	if (token->type & T_CONTROL_OPERATOR)
		return (next_token);
	return (NULL);
}
