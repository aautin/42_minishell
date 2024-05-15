/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:36:12 by aautin            #+#    #+#             */
/*   Updated: 2024/05/15 17:19:31 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "parser_utils.h"
#include "getenv.h"

static void	expand_len_insertion(t_list *envp, char *data[], size_t *expanded_len,
	int *mode)
{
	char	temp;
	char	*getenv_find;
	size_t	path_len;

	if (*mode == DB_QUOTE && **data == '"')
	{
		*mode = NO_QUOTE;
		*expanded_len += 2;
	}
	else
	{
		path_len = pathname_len(*data);
		if (path_len == 0)
			*expanded_len += 2;
		else
		{
			temp = (*data)[path_len];
			(*data)[path_len] = '\0';
			getenv_find = ft_getenv(envp, *data);
			(*data)[path_len] = temp;
			*data += path_len - 1;
			if (getenv_find != NULL)
				*expanded_len += ft_strlen(getenv_find);
		}
	}
}

static void	expand_data_insertion(t_list *envp, char *data[], char *new_data[])
{
	size_t	path_len;
	char	temp;
	char	*env;

	path_len = pathname_len(*data);
	if (path_len == 0)
	{
		*((*new_data)++) = '$';
		*((*new_data)++) = **data;
	}
	else
	{
		temp = (*data)[path_len];
		(*data)[path_len] = '\0';
		env = ft_getenv(envp, *data);
		(*data)[path_len] = temp;
		if (env != NULL)
		{
			ft_strlcat(*new_data, env, ft_strlen(env) + 1);
			*new_data += ft_strlen(env);
		}
		*data += path_len - 1;
	}
}

size_t	expand_len(t_expansion const *config, char data[])
{
	int		mode;
	size_t	expanded_len;

	mode = NO_QUOTE;
	expanded_len = 0;
	while (*data)
	{
		if (!config->ignore_quotes && (*data == '\'' || *data == '"'))
			change_quote_mode(*data, &mode);
		if (*data == '$' && mode != SG_QUOTE)
		{
			data++;
			if (*data == '?')
				expanded_len += nbr_len(config->exit_status);
			else
				expand_len_insertion(config->envp, &data, &expanded_len, &mode);
		}
		else
			expanded_len++;
		if (*data)
			data++;
	}
	return (expanded_len);
}

void	expand_data(t_expansion const *config, char data[], char new_data[])
{
	int		mode;

	mode = NO_QUOTE;
	while (*data != '\0')
	{
		if (!config->ignore_quotes && (*data == '\'' || *data == '"'))
			change_quote_mode(*data, &mode);
		if (*data == '$' && mode != SG_QUOTE)
		{
			if (*(++data) == '?')
				nbr_data(&new_data, config->exit_status);
			else if (mode == DB_QUOTE && *data == '"')
			{
				mode = NO_QUOTE;
				*(new_data++) = '$';
				*(new_data++) = '"';
			}
			else
				expand_data_insertion(config->envp, &data, &new_data);
		}
		else
			*(new_data++) = *data;
		if (*data != '\0')
			data++;
	}
}
