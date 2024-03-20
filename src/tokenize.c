/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 15:36:14 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft/libft.h"

#include "parser.h"
#include "tokenize_rules.h"
#include "tokenize_utils.h"

static int	parse_line(t_list **tokens, t_line_part *line_part);

int	tokenize(t_list **tokens, char line[])
{
	t_line_part	line_part;	

	line_part.token = ft_calloc(1, sizeof(t_token));
	if (line_part.token == NULL)
	{
		perror("tokenize():ft_calloc()");
		return (2);
	}
	line_part.token->type = T_NONE;
	line_part.line = line;
	line_part.index = 0;
	line_part.mode = NO_QUOTE;
	return (parse_line(tokens, &line_part));
}

t_list	*verify_tokens(t_list *tokens)
{
	t_token	*token;
	t_list	*next;
	int		is_redirect;

	token = tokens->content;
	if (token->type & T_CONTROL_OPERATOR)
		return (tokens);
	is_redirect = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (is_redirect && !(token->type & T_WORD))
			break ;
		if (token->type & T_REDIRECT_OPERATOR)
			is_redirect = 1;
		else
			is_redirect = 0;
		next = tokens->next;
		if (next == NULL && is_redirect)
			break ;
		tokens = tokens->next;
	}
	return (tokens);
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
