/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:12:39 by aautin            #+#    #+#             */
/*   Updated: 2024/03/11 20:22:31 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

#define NORMAL_MODE 0
#define QUOTE_MODE 1
#define DB_QUOTE_MODE 2

static void	parse_data(char *data, char *parsed_data, char **envp, char free)
{
	if (free)
		free(data);
}

int	parse_tokens(t_list *tokens, char **envp)
{
	unsigned int	i;
	unsigned int	len;
	t_token			*token;
	char			*parsed_data;

	while (tokens)
	{
		token = (t_token *) tokens->content;
		len = parsed_data_len(token->data, envp);
		if (len == -1)
			return (1);
		if (len != ft_strlen(token->data))
		{
			parsed_data = malloc((len + 1) * sizeof(char));
			if (token->data == NULL)
				return (1);
			parse_data(token->data, parsed_data, envp, 1);
		}
		else
			parse_data(token->data, token->data, envp, 0);
		tokens = tokens->next;
	}
	return (0);
}
