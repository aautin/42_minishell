/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/11 19:54:47 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

#define OPERATOR_TOKENS "<>|"
#define QUOTES_CHARS "\"\'"

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

t_token	*store_token(t_list **tokens, t_token *token, char line[], int len)
{
	token->data = ft_substr(line, 0, i);
	if (!add_to_list(tokens, token))
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		perror("tokenize():ft_calloc()");
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
		if (line[i] == '\0')
		{
			token->data = ft_substr(line, 0, i + 1);
			if (!add_to_list(tokens, token))
				return (0);
			break ;
		}
		if (token->type & T_OPERATOR && !quoted)
		{
			if (ft_strchr(OPERATOR_TOKENS, line[i]) != NULL)
			{
				if ((token->type & T_REDIRECT_OUTPUT))
				{
					if (line[i] == '>')
					{
						token->type &= ~T_REDIRECT_OUTPUT;
						token->type |= T_REDIRECT_APPEND;
					}
					else
					{
						free(token);
						return (0);
					}
				}
				else if ((token->type & T_REDIRECT_INPUT))
				{
					if (line[i] == '<')
					{
						token->type &= ~T_REDIRECT_INPUT;
						token->type |= T_REDIRECT_HERE_DOC;
					}
					else
					{
						free(token);
						return (0);
					}
				}
				else if ((token->type & T_REDIRECT_HERE_DOC) || (token->type & T_REDIRECT_APPEND))
				{
					free(token);
					return (0);
				}
				else if ((token->type & T_PIPE))
				{
					if (store_token(tokens, token, line, i) == NULL)
						return (0);
					token->type = T_WORD;
					line += i;
					i = 0;
					continue ;
				}
				i++;
			}
			else
			{
				token->data = ft_substr(line, 0, i);
				if (!add_to_list(tokens, token))
					return (0);
				token = ft_calloc(1, sizeof(t_token));
				if (token == NULL)
				{
					perror("tokenize():ft_calloc()");
					return (0);
				}
				if (ft_isspace(line[i]))
					token->type = T_NONE;
				else
					token->type = T_WORD;
				line += i;
				i = 0;
			}
			continue ;
		}
		if (ft_strchr(QUOTES_CHARS, line[i]) != NULL)
		{
			quoted ^= 1;
			i++;
			continue ;
		}
		if (!quoted && !(token->type & T_OPERATOR) && ft_strchr(OPERATOR_TOKENS, line[i]) != NULL)
		{
			if (token->type & T_WORD)
			{
				token->data = ft_substr(line, 0, i);
				if (!add_to_list(tokens, token))
					return (0);
				token = ft_calloc(1, sizeof(t_token));
				if (token == NULL)
				{
					perror("tokenize():ft_calloc()");
					return (0);
				}
				line += i;
				i = 0;
				continue ;
			}
			token->type = T_OPERATOR;
			if (line[i] == '>')
				token->type |= T_REDIRECT_OUTPUT;
			else if (line[i] == '<')
				token->type |= T_REDIRECT_INPUT;
			else
				token->type |= T_PIPE;
			i++;
			continue ;
		}
		if (!quoted && ft_isspace(line[i]))
		{
			if (i != 0)
			{
				token->data = ft_substr(line, 0, i);
				if (!add_to_list(tokens, token))
					return (0);
				token = ft_calloc(1, sizeof(t_token));
				if (token == NULL)
				{
					perror("tokenize():ft_calloc()");
					return (0);
				}
				line += i;
				i = 0;
			}
			else
			{
				line++;
				i = 0;
			}
			token->type = T_NONE;
			continue ;
		}
		if (token->type & T_WORD)
		{
			i++;
			continue ;
		}
		if (line[i] == '#')
		{
			free(token);
			break ;
		}
		token->type = T_WORD;
		i++;
	}
	return (!quoted);
}
