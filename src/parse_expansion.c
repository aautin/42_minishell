/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:36:12 by aautin            #+#    #+#             */
/*   Updated: 2024/03/20 20:32:45 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "parser_utils.h"

static void	expand_len_insertion(char *data[], int *expanded_len, int *mode)
{
	char	temp;
	char	*getenv_find;
	int		path_len;

	if (*mode == DB_QUOTE && **data == '"')
	{
		*mode = NO_QUOTE;
		*expanded_len += 2;
	}
	else
	{
		path_len = pathname_len(*data);
		if (path_len == -1)
			*expanded_len += 2;
		else
		{
			temp = (*data)[path_len];
			(*data)[path_len] = '\0';
			getenv_find = getenv(*data);
			(*data)[path_len] = temp;
			*data += path_len - 1;
			if (getenv_find != NULL)
				*expanded_len += ft_strlen(getenv_find);
		}
	}
}

static void	expand_data_insertion(char *data[], char *new_data[])
{
	int		path_len;
	char	temp;
	char	*env;

	path_len = pathname_len(*data);
	if (path_len == -1)
	{
		*(*new_data++) = '$';
		*(*new_data++) = **data;
	}
	else
	{
		temp = (*data)[path_len];
		(*data)[path_len] = '\0';
		env = getenv(*data);
		(*data)[path_len] = temp;
		if (env != NULL)
		{
			ft_strlcat(*new_data, env, ft_strlen(env) + 1);
			*new_data += ft_strlen(env);
		}
		*data += path_len - 1;
	}
}

int	expand_len(char data[])
{
	int		mode;
	int		expanded_len;

	mode = NO_QUOTE;
	expanded_len = 0;
	while (*data)
	{
		if (*data == '\'' || *data == '"')
			change_quote_mode(*data, &mode);
		if (*data == '$' && mode != SG_QUOTE)
		{
			data++;
			if (*data == '?')
				expanded_len++;
			else
				expand_len_insertion(&data, &expanded_len, &mode);
		}
		else
			expanded_len++;
		if (*data)
			data++;
	}
	return (expanded_len);
}

void	expand_data(char data[], char new_data[])
{
	int		mode;

	mode = NO_QUOTE;
	while (*data)
	{
		if (*data == '\'' || *data == '"')
			change_quote_mode(*data, &mode);
		if (*data == '$' && mode != SG_QUOTE)
		{
			data++;
			if (*data == '?')
				*(new_data++) = '0';
			else if (mode == DB_QUOTE && *data == '"')
			{
				mode = NO_QUOTE;
				*(new_data++) = '$';
				*(new_data++) = '"';
			}
			else
				expand_data_insertion(&data, &new_data);
		}
		else
			*(new_data++) = *data;
		if (*data)
			data++;
	}
}
