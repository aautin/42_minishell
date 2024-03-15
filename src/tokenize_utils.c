/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:43:03 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/15 17:57:24 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft/libft.h"

#include "parser.h"
#include "tokenize_utils.h"

int	add_to_list(t_list **tokens, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (node == NULL)
	{
		perror("add_to_list():ft_lstnew()");
		return (0);
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

t_token	*store_and_create_token(t_list **tokens, t_token *token,
		char line[], int len)
{
	token->data = ft_substr(line, 0, len);
	if (!add_to_list(tokens, token))
		return (NULL);
	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		perror("store_and_create_token():ft_calloc()");
	token->type = T_NONE;
	return (token);
}

t_action	append_redirect_operator(t_token *token, char c, int *i)
{
	if (ft_strchr(REDIRECT_OPERATOR, c) == NULL)
		return (0);
	if (c == '>')
	{
		if (token->type & T_REDIRECT_OUTPUT)
		{
			token->type &= ~T_REDIRECT_OUTPUT;
			token->type |= T_REDIRECT_APPEND;
			(*i)++;
			return (A_CONTINUE);
		}
	}
	else if (c == '<')
	{
		if ((token->type & T_REDIRECT_INPUT))
		{
			token->type &= ~T_REDIRECT_INPUT;
			token->type |= T_REDIRECT_HERE_DOC;
			(*i)++;
			return (A_CONTINUE);
		}
	}
	return (A_NONE);
}

t_action	new_operator(t_list **tokens, t_token **token,
		char *line[], int *i)
{
	if (ft_strchr(OPERATOR_TOKENS, (*line)[*i]) == NULL)
		return (A_NONE);
	if ((*token)->type & T_WORD)
	{
		*token = store_and_create_token(tokens, *token, *line, *i);
		if (*token == NULL)
			return (A_RETURN);
		*line += *i;
		*i = 0;
	}
	(*token)->type = T_OPERATOR;
	if ((*line)[*i] == '>')
		(*token)->type |= T_REDIRECT_OPERATOR | T_REDIRECT_OUTPUT;
	else if ((*line)[*i] == '<')
		(*token)->type |= T_REDIRECT_OPERATOR | T_REDIRECT_INPUT;
	else if ((*line)[*i] == '|')
		(*token)->type |= T_CONTROL_OPERATOR | T_PIPE;
	(*i)++;
	return (A_CONTINUE);
}

t_action	ignore_blank(t_list **tokens, t_token **token,
		char *line[], int *i)
{
	if (!ft_isspace((*line)[*i]))
		return (A_NONE);
	if ((*token)->type != T_NONE)
	{
		*token = store_and_create_token(tokens, *token, *line, *i);
		if (*token == NULL)
			return (A_RETURN);
		*line += *i + 1;
		*i = 0;
	}
	else
		(*line)++;
	(*token)->type = T_NONE;
	return (A_CONTINUE);
}
