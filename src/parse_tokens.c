/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/03/12 17:30:25 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

#define NORMAL_MODE 0
#define QUOTE_MODE 1
#define DB_QUOTE_MODE 2

// static void	parse_data(char *data, char	*parsed_data)
// {
// 	char			mode;
// 	unsigned int	i;

// 	mode = NORMAL_MODE;
// 	i = 0;
// 	while (data[i])
// 	{
// 		if (data[i] == '"' && mode != QUOTE_MODE)
// 		{
// 			if (mode == NORMAL_MODE)
// 				mode = DB_QUOTE_MODE;
// 			else if (mode == DB_QUOTE_MODE)
// 				mode = NORMAL_MODE;
// 			data_len--;
// 		}
// 		else if (data[i] == '\'' && mode != DB_QUOTE_MODE)
// 		{
// 			if (mode == NORMAL_MODE)
// 				mode = QUOTE_MODE;
// 			else if (mode == QUOTE_MODE)
// 				mode = NORMAL_MODE;
// 			data_len--;
// 		}
// 		else if (data[i] == '$' && mode != QUOTE_MODE)
// 			data_len += expansion_len(&data[i + 1], &i);
// 		i++;
// 	}
// }

static int	expansion_len(char *pathname, unsigned int *i)
{
	unsigned int	len;
	char			temp;

	if (pathname[0] == '?')
	{
		*i += 1;																// here, have to place the previous EXIT_STATUS
		return (-1);															// 	-> for now, just place substitute $? with 0
	}
	len = 0;
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	*i += len;																	// here, move the index browsing in token->data
	if (len == 0)																// at the end of expension_pathname, examples:
		return (0);																// 	-> "$HOME qe": on the E	->"$? ": on the ?
	temp = pathname[len];
	pathname[len] = '\0';
	if (getenv(pathname) == NULL)
		return (-len - 1);
	return (ft_strlen(getenv(pathname)) - len - 1);
}

#include <stdio.h>

int	parse_data_len(char *data, int data_len)
{
	char			mode;
	unsigned int	i;

	mode = NORMAL_MODE;
	i = 0;
	while (data[i])
	{
		if (data[i] == '"' && mode != QUOTE_MODE)
		{
			if (mode == NORMAL_MODE)
				mode = DB_QUOTE_MODE;
			else if (mode == DB_QUOTE_MODE)
				mode = NORMAL_MODE;
			data_len--;
		}
		else if (data[i] == '\'' && mode != DB_QUOTE_MODE)
		{
			if (mode == NORMAL_MODE)
				mode = QUOTE_MODE;
			else if (mode == QUOTE_MODE)
				mode = NORMAL_MODE;
			data_len--;
		}
		else if (data[i] == '$' && mode != QUOTE_MODE)
			data_len += expansion_len(&data[i + 1], &i);
		i++;
	}
	printf("%s: %d\n", data, data_len);
	return (data_len);
}

static int	parse_token(t_token *token)
{
	int		len;
	char	*parsed_data;

	len = parse_data_len(token->data, ft_strlen(token->data));
	if (len == -1)
		return (1);
	parsed_data = malloc((len + 1) * sizeof(char));
	if (parsed_data == NULL)
		return (1);
	ft_bzero(parsed_data, len + 1);
	// parse_data(token->data, parsed_data);
	free(token->data);
	token->data = parsed_data;
	return (0);
}

int	parse_tokens(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = (t_token *) tokens->content;
		if ((token->type & T_PIPE) == 0)
		{
			if (parse_token(token) == 1)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
