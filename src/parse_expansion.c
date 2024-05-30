/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:36:12 by aautin            #+#    #+#             */
/*   Updated: 2024/05/30 18:47:09 by aautin           ###   ########.fr       */
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
	while (data[start] != '\0')
	{
		if (data[start] == '$' && data[start + 1] == '?')
			end = start + 1;
		else if (data[start] == '$')
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

static int	expansion(t_list *component, t_list *envp, 
			unsigned char exit_status)
{
	char	*data;
	char	*env;

	data = (char *) component->content;
	if (data[1] == '?')
	{
		env = ft_itoa(exit_status);
		if (env == NULL)
			return (perror("parse_components():ft_itoa()"), 1);
	}
	else
	{
		env = ft_getenv(envp, &data[1]);
		if (env != NULL)
		{
			env = ft_strdup(env);
			if (env == NULL)
				return (perror("parse_components():ft_strdup()"), 1);
		}
	}
	if (env == NULL)
		return (0);
	free(component->content);
	component->content = env;
	return (0);
}

int	parse_components(t_expansion const *config, t_list *components)
{
	int		mode;
	char	*data;

	mode = NO_QUOTE;
	while (components != NULL)
	{
		data = (char *) components->content;
		if (data[0] == '$' && mode != SG_QUOTE)
		{
			if (expansion(components, config->envp, config->exit_status) == 1)
				return (1);
		}
		else if (config->ignore_quotes == 0)
			mode = unquote(data, mode);
		components = components->next;
	}
	return (0);
}

int	components_to_data(t_token *token, t_list *components)
{
	size_t	len;
	t_list	*head;
	char	*new_data;

	len = 0;
	head = components;
	while (components)
	{
		len += ft_strlen((char *) components->content);
		components = components->next;
	}
	new_data = malloc((len + 1) * sizeof(char));
	if (new_data == NULL)
		return (1);
	new_data[0] = '\0';
	components = head;
	while (components)
	{
		ft_strlcat(new_data, (char *) components->content, len + 1);
		components = components->next;
	}
	free(token->data);
	token->data = new_data;
	return (0);
}