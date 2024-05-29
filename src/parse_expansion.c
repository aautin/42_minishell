/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:36:12 by aautin            #+#    #+#             */
/*   Updated: 2024/05/29 22:00:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "parser_utils.h"
#include "getenv.h"


static t_list	*create_component(char data[], int len)
{
	t_list	*component;
	char	*data_cpy;

	data_cpy = malloc((len + 1) * sizeof(char));
	if (data_cpy == NULL)
		return (NULL);
	data_cpy[0] = '\0';
	ft_strlcat(data_cpy, data, len + 1);
	component = ft_lstnew(data_cpy);
	if (component == NULL)
		free(data_cpy);
	return (component);
}

t_list	*get_token_components(char data[])
{
	t_list	*components;
	t_list	*component;
	int		start;
	int		end;

	components = NULL;
	start = 0;
	while (data[start])
	{
		if (data[start] == '$')
			end = start + pathname_len(&data[start + 1]);
		else
		{
			end = start;
			while (data[end + 1] != '\0' && data[end + 1] != '$')
				end++;
		}
		component = create_component(&data[start], end - start + 1);
		if (component == NULL)
			return (ft_lstclear(&components, free), NULL);
		ft_lstadd_back(&components, component);
		start = end + 1;
	}
	return (components);
}

int	parse_components(t_expansion const *config, t_list *components)
{
	int		mode;
	char	*data;
	char	*env;

	mode = NO_QUOTE;
	while (components != NULL)
	{
		data = (char *) components->content;
		if (data[0] == '$' && mode != SG_QUOTE)
		{
			env = ft_getenv(config->envp, &data[1]);
			if (env != NULL)
			{
				env = ft_strdup(env);
				if (env == NULL)
					return (1);
				free(components->content);
				components->content = env;
			}
		}
		else
			mode = unquote(data, mode);
		components = components->next;
	}
	return (0);
}
