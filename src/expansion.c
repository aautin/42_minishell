/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:36:12 by aautin            #+#    #+#             */
/*   Updated: 2024/03/19 20:26:03 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

static int	pathname_len(char *pathname)
{
	int	len;

	len = 0;
	if (!ft_isalpha(pathname[len]))
		return (-1);
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	return (len);
}

void	expansion(char **data, char **new_data, char *mode)
{
	int		len;
	char	temp;
	char	*var_value;

	(*data)++;
	if (**data == '?')
	{
		*(*new_data++) = '0';
		(*data)++;
	}
	else if ((*mode == DB_QUOTE && **data == '"') || pathname_len(*data) == -1)
		*(*new_data++) = '$';
	else
	{
		len = pathname_len(*data);
		temp = (*data)[len];
		(*data)[len] = '\0';
		var_value = getenv(*data);
		(*data)[len] = temp;
		(*data += len);
		if (var_value != NULL)
		{
			ft_strlcpy(*new_data, var_value, ft_strlen(var_value) + 1);
			(*new_data) += ft_strlen(var_value);
		}
	}
}

int	expansion_len(char **data, char *mode)
{
	int		len;
	char	temp;
	char	*var_value;

	(*data)++;
	if (**data == '?')
		return ((*data)++, 1);
	if (*mode == DB_QUOTE && **data == '"')
		return (1);
	len = pathname_len(*data);
	if (len == -1)
		return (1);
	temp = (*data)[len];
	(*data)[len] = '\0';
	var_value = getenv(*data);
	(*data)[len] = temp;
	*data += len;
	if (var_value == NULL)
		return (0);
	return (ft_strlen(var_value));
}
