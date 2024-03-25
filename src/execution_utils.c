/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:55:27 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 19:08:52 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "minishell.h"
#include "parser.h"
#include "utils.h"

int	find_args(t_list **args, t_minishell *ms, t_list *current_token, t_list *last_token)
{
	(void)ms;
	int		is_redirection;
	t_token	*token;

	is_redirection = 0;
	while (current_token != last_token)
	{
		token = current_token->content;
		if (token->type & T_REDIRECT_OPERATOR)
			is_redirection = 1;
		else if (token->type & T_WORD)
		{
			if (!is_redirection)
			{
				parse_token(token);
				if (*token->data != '\0' && add_to_list(args, token))
				{
					ft_lstclear(args, NULL);
					return (1);
				}
			}
			is_redirection = 0;
		}
		current_token = current_token->next;
	}
	return (0);
}

t_list	*get_control_operator(t_list *current_token)
{
	t_token	*token;

	while (current_token != NULL)
	{
		token = current_token->content;
		if (token->type & T_CONTROL_OPERATOR)
			break ;
		current_token = current_token->next;
	}
	return (current_token);
}

char	**listtoken_to_tabstr(t_list *current_token)
{
	int				i;
	t_token			*token;
	int const		size = ft_lstsize(current_token);
	char **const	tab = malloc((size + 1) * sizeof(char *));

	if (tab == NULL)
	{
		perror("listtoken_to_tabstr():malloc()");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		token = current_token->content;
		tab[i] = token->data;
		current_token = current_token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	goto_next_here_doc(t_minishell *ms, t_list *current_token, t_list *last_token)
{
	t_token	*token;

	while (current_token != last_token)
	{
		token = current_token->content;
		if (token->type & T_REDIRECT_HERE_DOC)
		{
			ms->current_here_doc = ms->current_here_doc->next;
			current_token = current_token->next;
		}
		current_token = current_token->next;
	}
}
