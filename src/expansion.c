/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:36:12 by aautin            #+#    #+#             */
/*   Updated: 2024/03/16 11:58:53 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

static unsigned int	pathname_len(char *pathname)
{
	unsigned int	len;

	len = 0;
	if (!ft_isalpha(pathname[len]))
		return (1);
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	return (len);
}

int	expansion(char *data, char *parsed_data, char *mode, unsigned int *parsed_i)
{
	unsigned int	len;
	char			temp;
	char			*var_value;

	if (*mode == DB_QUOTE && (data[0] == '\'' || data[0] == '"'))
	{
		parsed_data[*parsed_i] = '$';
		if (data[0] == '"')
			return (*mode = NO_QUOTE, *parsed_i += 1, 2);
		return (parsed_data[*parsed_i + 1] = data[0], *parsed_i += 2, 2);
	}
	else if (data[0] == '?')
		return (parsed_data[*parsed_i] = '0', 2);
	len = pathname_len(data);
	if (len == 0)
		return (parsed_data[*parsed_i] = '$', *parsed_data += 1, 1);
	temp = data[len];
	data[len] = '\0';
	var_value = getenv(data);
	data[len] = temp;
	if (var_value == NULL)
		return (len + 1);
	ft_strlcpy(&parsed_data[*parsed_i], var_value, ft_strlen(var_value) + 1);
	return (*parsed_i += ft_strlen(var_value), len + 1);
}

int	expansion_len(char *pathname, char *mode, unsigned int *i)
{
	unsigned int	len;
	char			temp;
	char			*var_value;

	if (*mode == DB_QUOTE && pathname[0] == '\'')
		return (*i += 1, 0);
	if (*mode == DB_QUOTE && pathname[0] == '"')
		return (*i += 1, *mode = NO_QUOTE, -1);
	else if (pathname[0] == '?')
		return (*i += 1, -1);
	len = pathname_len(pathname);
	*i += len;
	if (len == 0)
		return (-1);
	temp = pathname[len];
	pathname[len] = '\0';
	var_value = getenv(pathname);
	pathname[len] = temp;
	if (var_value == NULL)
		return (-len - 1);
	return (ft_strlen(var_value) - len - 1);
}
