/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:39:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 13:48:50 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "tokenize_utils.h"

t_action	rule_1(t_list **tokens, t_token *token, char line[], int i)
{
	if (line[i] != '\0')
		return (A_NONE);
	if (token->type == T_NONE)
	{
		free(token);
		return (A_BREAK);
	}
	token->data = ft_substr(line, 0, i);
	if (add_to_list(tokens, token))
		return (A_RETURN);
	return (A_BREAK);
}

t_action	rule_2_3(t_list **tokens, t_token **token, char *line[], int *i)
{
	t_action	action;

	action = A_NONE;
	if (!((*token)->type & T_OPERATOR))
		return (A_NONE);
	if ((*token)->type & T_REDIRECT_OPERATOR)
		action = append_redirect_operator(*token, (*line)[*i], i);
	if (action != A_NONE)
		return (action);
	*token = store_and_create_token(tokens, *token, *line, *i);
	if (*token == NULL)
		return (A_RETURN);
	*line += *i;
	*i = 0;
	return (A_CONTINUE);
}

t_action	rule_4(t_token *token, char c, int *i, int *quoted)
{
	if (ft_strchr(QUOTE_CHARS, c) == NULL)
		return (A_NONE);
	if (c == '\'')
	{
		if (*quoted == NO_QUOTE)
			*quoted = SG_QUOTE;
		else if (*quoted == SG_QUOTE)
			*quoted = NO_QUOTE;
	}
	else if (c == '"')
	{
		if (*quoted == NO_QUOTE)
			*quoted = DB_QUOTE;
		else if (*quoted == DB_QUOTE)
			*quoted = NO_QUOTE;
	}
	token->type = T_WORD | T_QUOTED;
	(*i)++;
	return (A_CONTINUE);
}

t_action	rule_6_7(t_list **tokens, t_token **token, char *line[], int *i)
{
	t_action	action;

	action = new_operator(tokens, token, line, i);
	if (action != A_NONE)
		return (action);
	action = ignore_blank(tokens, token, line, i);
	return (action);
}

t_action	rule_8_9_10(t_token **token, char line[], int *i)
{
	if ((*token)->type & T_WORD)
	{
		(*i)++;
		return (A_CONTINUE);
	}
	if (line[*i] == '#')
	{
		if ((*token)->type == T_NONE)
		{
			free(*token);
			*token = NULL;
		}
		return (A_BREAK);
	}
	(*token)->type = T_WORD;
	(*i)++;
	return (A_CONTINUE);
}
