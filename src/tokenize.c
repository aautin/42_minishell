/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/13 21:20:04 by pnguyen-         ###   ########.fr       */
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
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		perror("store_and_create_token():ft_calloc()");
	token->type = T_NONE;
	return (token);
}

int	tokenize(t_list **tokens, char line[])
{
	t_token	*token;
	int		i;
	int		quoted;

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
			token->data = ft_substr(line, 0, i + 1);
			if (!add_to_list(tokens, token))
				return (0);
			break ;
		}
		if (token->type & T_OPERATOR)
		{
			// RULE #2
			if (token->type & T_REDIRECT_OPERATOR)
			{
				if (ft_strchr(REDIRECT_OPERATOR, line[i]) != NULL)
				{
					if (line[i] == '>')
					{
						if (token->type & T_REDIRECT_OUTPUT)
						{
							token->type &= ~T_REDIRECT_OUTPUT;
							token->type |= T_REDIRECT_APPEND;
							i++;
							continue ;
						}
					}
					if (line[i] == '<')
					{
						if ((token->type & T_REDIRECT_INPUT))
						{
							token->type &= ~T_REDIRECT_INPUT;
							token->type |= T_REDIRECT_HERE_DOC;
							i++;
							continue ;
						}
					}
					//if (line[i] == '|'
					//		|| (token->type & T_PIPE)
					//		|| (token->type & T_REDIRECT_HERE_DOC)
					//		|| (token->type & T_REDIRECT_APPEND))
					//{
					//	token = store_and_create_token(tokens, token, line, i);
					//	if (token == NULL)
					//		return (0);
					//	line += i;
					//	i = 0;
					//	continue ;
					//}
				}
			}
		// RULE #3
		//	else
		//	{
			token = store_and_create_token(tokens, token, line, i);
			if (token == NULL)
				return (0);
			line += i;
			i = 0;
			continue ;
		//	}
		}
		// RULE #4
		if (ft_strchr(QUOTE_CHARS, line[i]) != NULL)
		{
			if (line[i] == '\'')
			{
				if (quoted == NO_QUOTE)
					quoted = SG_QUOTE;
				else if (quoted == SG_QUOTE)
					quoted = NO_QUOTE;
			}
			else if (line[i] == '"')
			{
			   if (quoted == NO_QUOTE)
				   quoted = DB_QUOTE;
			   else if (quoted == DB_QUOTE)
					quoted = NO_QUOTE;
			}
			token->type = T_WORD;
			i++;
			continue ;
		}
		// RULE #6
		if (quoted == NO_QUOTE && ft_strchr(OPERATOR_TOKENS, line[i]) != NULL)
		{
			if (token->type & T_WORD)
			{
				token = store_and_create_token(tokens, token, line, i);
				if (token == NULL)
					return (0);
				line += i;
				i = 0;
			}
			token->type = T_OPERATOR;
			if (line[i] == '>')
				token->type |= T_REDIRECT_OPERATOR | T_REDIRECT_OUTPUT;
			else if (line[i] == '<')
				token->type |= T_REDIRECT_OPERATOR | T_REDIRECT_INPUT;
			else
				token->type |= T_CONTROL_OPERATOR | T_PIPE;
			i++;
			continue ;
		}
		// RULE #7
		if (quoted == NO_QUOTE && ft_isspace(line[i]))
		{
			if (token->type != T_NONE)
			{
				token = store_and_create_token(tokens, token, line, i);
				if (token == NULL)
					return (0);
				line += i + 1;
				i = 0;
			}
			else
				line++;
			token->type = T_NONE;
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
		{
			token->data = ft_substr(line, 0, i + 1);
			if (!add_to_list(tokens, token))
				return (0);
			break ;
		}
		// RULE #10
		token->type = T_WORD;
		i++;
	}
	return (quoted == NO_QUOTE);
}
