/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:55:27 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 20:41:31 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "parser.h"

int		add_to_list(t_list **tokens, t_token *token);

int	find_args(t_list *current, t_list *last, t_list **args)
{
	int		is_redirection;
	t_token	*token;

	is_redirection = 0;
	while (current != last)
	{
		token = current->content;
		if (token->type & T_REDIRECT_OPERATOR)
			is_redirection = 1;
		else if (token->type & T_WORD)
		{
			if (!is_redirection)
			{
				if (add_to_list(args, token))
				{
					ft_lstclear(args, NULL);
					return (1);
				}
			}
			is_redirection = 0;
		}
		current = current->next;
	}
	return (0);
}

t_list	*get_control_operator(t_list *current)
{
	t_token	*token;

	while (current != NULL)
	{
		token = current->content;
		if (token->type & T_CONTROL_OPERATOR)
			break ;
		current = current->next;
	}
	return (current);
}

char	**listtoken_to_tabstr(t_list *current)
{
	int				i;
	t_token			*token;
	int const		size = ft_lstsize(current);
	char **const	tab = malloc((size + 1) * sizeof(char *));

	if (tab == NULL)
	{
		perror("listtoken_to_tabstr():malloc()");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		token = current->content;
		parse_token(token);
		tab[i] = token->data;
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
