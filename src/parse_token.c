/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/05/29 20:52:55 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"
#include "parser_utils.h"

void	unquote(char data[])
{
	int	mode;

	mode = NO_QUOTE;
	while (*data)
	{
		if (*data == '\'' && (mode == NO_QUOTE || mode == SG_QUOTE))
		{
			if (mode == SG_QUOTE)
				mode = NO_QUOTE;
			else if (mode == NO_QUOTE)
				mode = SG_QUOTE;
			ft_memmove(data, data + 1, ft_strlen(data + 1) + 1);
		}
		else if (*data == '"' && (mode == NO_QUOTE || mode == DB_QUOTE))
		{
			if (mode == DB_QUOTE)
				mode = NO_QUOTE;
			else if (mode == NO_QUOTE)
				mode = DB_QUOTE;
			ft_memmove(data, data + 1, ft_strlen(data + 1) + 1);
		}
		else
			data++;
	}
}

t_list	*create_component(char data[], int len)
{
	t_list	*component;
	char	*data_cpy;

	data_cpy = malloc((len + 1) * sizeof(char));
	if (data_cpy == NULL)
		return (perror("create_component():malloc()"), NULL);
	data_cpy[0] = '\0';
	ft_strlcat(data_cpy, data, len + 1);
	component = ft_lstnew(data_cpy);
	if (component == NULL)
	{
		free(data_cpy);
		perror("create_component():ft_lstnew()");
	}
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
	end = 0;
	while (data[start])
	{
		if (data[start] == '$')
			end = start + 1 + pathname_len(data[start + 1]);
		else
		{
			end = start;
			while (data[end + 1] != '\0' && data[end + 1] != '$')
				end++;
		}
		component = create_component(&data[start], end - start);
		if (component == NULL)
			return (ft_lstclear(&components, free), NULL);
		ft_lstadd_back(&components, component);
		start = end;
	}
	return (components);
}


static int	expansion(t_token *token, t_list *envp, int ignore_quotes,
	int exit_status)
{
	t_expansion const	config = {envp, exit_status, ignore_quotes};
	char				*expanded_data;
	size_t				expanded_len;
	t_list				*components;

	components = get_token_components(token->data);
	while (components) {
		printf("%s\n", (char *) components->content);
		components = components->next;
	}
	if (components == NULL)
	{
		perror("parse_token():malloc()");
		return (1);
	}
	return (0);
}

static void	turn_to_abs(char str[])
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 0)
			str[i] = -str[i];
		i++;
	}
}

int	parse_token(t_token *token, t_list *envp, int exit_status,
	int ignore_quotes)
{
	if (expansion(token, envp, ignore_quotes, exit_status))
		return (1);
	if (!ignore_quotes)
		unquote(token->data);
	turn_to_abs(token->data);
	return (0);
}
