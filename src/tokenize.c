/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:44 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 13:34:06 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft/libft.h"

#include "parser.h"
#include "tokenize_rules.h"
#include "tokenize_utils.h"

static t_action	apply_rules_first_part(t_list **tokens, t_token **token,
		char *line[], int *i)
{
	t_action	action;

	action = rule_1(tokens, *token, *line, *i);
	if (action != A_NONE)
		return (action);
	action = rule_2_3(tokens, token, line, i);
	return (action);
}

static int	parse_line(t_list **tokens, char line[], t_token *token, int i)
{
	int			quoted;
	t_action	action;

	quoted = NO_QUOTE;
	while (1)
	{
		action = apply_rules_first_part(tokens, &token, &line, &i);
		if (action == A_NONE)
			action = rule_4(token, line[i], &i, &quoted);
		if (action == A_NONE && quoted == NO_QUOTE)
			action = rule_6_7(tokens, &token, &line, &i);
		if (action == A_NONE)
			action = rule_8_9_10(&token, line, &i);
		if (action == A_BREAK)
			break ;
		if (action == A_RETURN)
			return (2);
	}
	return (quoted != NO_QUOTE);
}

int	tokenize(t_list **tokens, char line[])
{
	t_token		*token;
	int			i;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
	{
		perror("tokenize():ft_calloc()");
		return (2);
	}
	token->type = T_NONE;
	while (ft_isspace(*line))
		line++;
	i = 0;
	return (parse_line(tokens, line, token, i));
}
