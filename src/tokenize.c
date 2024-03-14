/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/14 11:21:54 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

#define REDIRECT_OPERATOR "<>"
#define CONTROL_OPERATOR "|"
#define OPERATOR_TOKENS CONTROL_OPERATOR REDIRECT_OPERATOR
#define QUOTE_CHARS "\"'"

#define NO_QUOTE 0
#define SG_QUOTE 1
#define DB_QUOTE 2


static int	add_to_list(t_list **tokens, t_token *token)
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

static t_token	*store_and_create_token(t_list **tokens, t_token *token,
		char line[], int len)
{
	token->data = ft_substr(line, 0, len);
	if (!add_to_list(tokens, token))
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		perror("store_and_create_token():ft_calloc()");
	token->type = T_NONE;
	return (token);
}

static int	append_redirect_operator(t_token *token, char c, int *i)
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
			return (1);
		}
	}
	else if (c == '<')
	{
		if ((token->type & T_REDIRECT_INPUT))
		{
			token->type &= ~T_REDIRECT_INPUT;
			token->type |= T_REDIRECT_HERE_DOC;
			(*i)++;
			return (1);
		}
	}
	return (0);
}

static int	toggle_quote(t_token *token, char c, int *i, int *quoted)
{
	if (ft_strchr(QUOTE_CHARS, c) == NULL)
		return (0);
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
	token->type = T_WORD;
	(*i)++;
	return (1);
}

static int	new_operator(t_list **tokens, t_token **token, char *line[], int *i)
{
	if (ft_strchr(OPERATOR_TOKENS, (*line)[*i]) == NULL)
		return (0);
	if ((*token)->type & T_WORD)
	{
		*token = store_and_create_token(tokens, *token, *line, *i);
		if (*token == NULL)
			return (-1);
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
	return (1);
}

static int	ignore_blank(t_list **tokens, t_token **token, char *line[], int *i)
{
	if (!ft_isspace((*line)[*i]))
		return (0);
	if ((*token)->type != T_NONE)
	{
		*token = store_and_create_token(tokens, *token, *line, *i);
		if (*token == NULL)
			return (-1);
		*line += *i + 1;
		*i = 0;
	}
	else
		(*line)++;
	(*token)->type = T_NONE;
	return (1);
}

int	tokenize(t_list **tokens, char line[])
{
	t_token	*token;
	int		i;
	int		quoted;
	int		status;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
	{
		perror("tokenize():ft_calloc()");
		return (0);
	}
	while (ft_isspace(*line))
		line++;
	i = 0;
	quoted = 0;
	while (1)
	{
		// RULE #1
		if (line[i] == '\0')
		{
			if (token->type == T_NONE)
				break ;
			token->data = ft_substr(line, 0, i);
			if (!add_to_list(tokens, token))
				return (0);
			break ;
		}
		if (token->type & T_OPERATOR)
		{
			// RULE #2
			if (token->type & T_REDIRECT_OPERATOR)
			{
				if (append_redirect_operator(token, line[i], &i))
					continue ;
			}
			// RULE #3
			token = store_and_create_token(tokens, token, line, i);
			if (token == NULL)
				return (0);
			line += i;
			i = 0;
			continue ;
		}
		// RULE #4
		if (toggle_quote(token, line[i], &i, &quoted))
			continue ;
		if (quoted == NO_QUOTE)
		{
			// RULE #6
			status = new_operator(tokens, &token, &line, &i);
			if (status == -1)
				return (0);
			if (status == 1)
				continue ;
			// RULE #7
			status = ignore_blank(tokens, &token, &line, &i);
			if (status == -1)
				return (0);
			if (status == 1)
				continue ;
		}
		// RULE #8
		if (token->type & T_WORD)
		{
			i++;
			continue ;
		}
		// RULE #9
		if (line[i] == '#')
			break ;
		// RULE #10
		token->type = T_WORD;
		i++;
	}
	return (quoted == NO_QUOTE);
}
