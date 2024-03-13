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

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

// TODO: to rename and move in parser.h
#define NORMAL_MODE 0
#define QUOTE_MODE 1
#define DB_QUOTE_MODE 2

static int	expansion(char *pathname, char *parsed_data, char *mode, unsigned int *parsed_i)
{
	unsigned int	len;
	char			temp;
	char			*var_value;

	if (*mode == DB_QUOTE_MODE && pathname[0] == '\'')
	{
		parsed_data[*parsed_i] = '$';
		parsed_data[*parsed_i + 1] = '\'';
		return (*parsed_i += 2, 2);
	}
	if (*mode == DB_QUOTE_MODE && pathname[0] == '"')
		return (*mode = NORMAL_MODE, 2);
	else if (pathname[0] == '?')
		return (parsed_data[*parsed_i] = '0', 2);								// here, have to place the previous EXIT_STATUS
	len = 0;																	// 	-> for now, just place substitute $? with 0
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	if (len == 0)
		return (parsed_data[*parsed_i] = '$', *parsed_data += 1, 1);
	temp = pathname[len];
	pathname[len] = '\0';
	var_value = getenv(pathname);
	pathname[len] = temp;
	if (var_value == NULL)
		return (len + 1);
	return (ft_strlcpy(&parsed_data[*parsed_i], var_value, ft_strlen(var_value) + 1), *parsed_i += ft_strlen(var_value), len + 1);
}

static void	parse_data(char *data, char *parsed_data)
{
	unsigned int	i;
	unsigned int	parsed_i;
	char			mode;

	mode = NORMAL_MODE;
	i = 0;
	parsed_i = 0;
	while (data[i])
	{
		if (data[i] == '"' && mode != QUOTE_MODE)
		{
			if (mode == NORMAL_MODE)
				mode = DB_QUOTE_MODE;
			else if (mode == DB_QUOTE_MODE)
				mode = NORMAL_MODE;
			i++;
		}
		else if (data[i] == '\'' && mode != DB_QUOTE_MODE)
		{
			if (mode == NORMAL_MODE)
				mode = QUOTE_MODE;
			else if (mode == QUOTE_MODE)
				mode = NORMAL_MODE;
			i++;
		}
		else if (data[i] == '$' && mode != QUOTE_MODE)
			i += expansion(&data[i + 1], parsed_data, &mode, &parsed_i);
		else
		{
			parsed_data[parsed_i] = data[i];
			i++;
			parsed_i++;
		}
	}
	// TODO: avoid to overwrite '\0' at the end of the new_data
	printf("%s\n", parsed_data);
}

static int	expansion_len(char *pathname, char *mode, unsigned int *i)
{
	unsigned int	len;
	char			temp;
	char			*var_value;

	if (*mode == DB_QUOTE_MODE && pathname[0] == '\'')
		return (*i += 1, 0);
	// TODO: make the $ sign staying
	if (*mode == DB_QUOTE_MODE && pathname[0] == '"') 
		return (*i += 1, *mode = NORMAL_MODE, -2);
	else if (pathname[0] == '?')
		return (*i += 1, -1);													// here, have to place the previous EXIT_STATUS
	len = 0;																	// 	-> for now, just place substitute $? with 0
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	*i += len;																	// here, move the index browsing in token->data
	if (len == 0)																// at the end of expension_pathname, examples:
		return (-1);															// 	-> "$HOME qe": on the E	->"$? ": on the ?
	temp = pathname[len];
	pathname[len] = '\0';
	var_value = getenv(pathname);
	pathname[len] = temp;
	if (var_value == NULL)
		return (-len - 1);
	return (ft_strlen(var_value) - len - 1);
}

int	parse_data_len(char *data, int data_len)
{
	unsigned int	i;
	char			mode;

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
			data_len += expansion_len(&data[i + 1], &mode, &i);
		i++;
	}
	return (printf("%s: %d\n", data, data_len), data_len);
}

static int	parse_token(t_token *token)
{
	unsigned int	len;
	char			*parsed_data;

	len = parse_data_len(token->data, ft_strlen(token->data));
	parsed_data = malloc((len + 1) * sizeof(char));
	if (parsed_data == NULL)
		return (1);
	parse_data(token->data, parsed_data);
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
		// TODO: don't parse other things than the T_WORD type
		if ((token->type & T_PIPE) == 0)
		{
			if (parse_token(token) == 1)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
