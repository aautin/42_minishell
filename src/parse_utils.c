/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:36:12 by aautin            #+#    #+#             */
/*   Updated: 2024/05/30 20:49:19 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "getenv.h"

size_t	pathname_len(char const pathname[])
{
	size_t	len;

	len = 0;
	if (!ft_isalpha(pathname[0]) && pathname[0] != '_')
		return (0);
	while (ft_isalnum(pathname[len]) || pathname[len] == '_')
		len++;
	return (len);
}

int	expansion(t_list *component, t_list *envp,
		unsigned char exit_status)
{
	char	*data;
	char	*env;

	data = (char *) component->content;
	if (data[1] == '?')
	{
		env = ft_itoa(exit_status);
		if (env == NULL)
			return (perror("expansion():ft_itoa()"), 1);
	}
	else
	{
		env = ft_getenv(envp, &data[1]);
		if (env != NULL)
		{
			env = ft_strdup(env);
			if (env == NULL)
				return (perror("expansion():ft_strdup()"), 1);
		}
	}
	if (env == NULL)
		return (0);
	free(component->content);
	component->content = env;
	return (0);
}
