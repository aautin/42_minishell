/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:55:27 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/30 19:52:58 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "list_utils.h"
#include "minishell.h"
#include "parser.h"

static int	add_to_args(t_list **args, t_list **last_node,
				t_token *token, t_minishell *ms);

int	find_args(t_list **args, t_minishell *ms,
		t_list *current_token, t_list *last_token)
{
	int		is_redirection;
	t_token	*token;
	t_list	*last_node;

	is_redirection = 0;
	last_node = NULL;
	while (current_token != last_token)
	{
		token = current_token->content;
		if (token->type & T_REDIRECT_OPERATOR)
			is_redirection = 1;
		else if (token->type & T_WORD)
		{
			if (!is_redirection)
			{
				if (add_to_args(args, &last_node, token, ms))
					return (1);
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

char	**listtoken_to_tabstr(t_list *args)
{
	int				i;
	t_token			*token;
	int const		size = ft_lstsize(args);
	char **const	tab = malloc((size + 1) * sizeof(char *));

	if (tab == NULL)
	{
		perror("listtoken_to_tabstr():malloc()");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		token = args->content;
		tab[i] = token->data;
		args = args->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	goto_next_heredoc(t_minishell *ms,
		t_list *current_token, t_list *last_token)
{
	t_token	*token;

	while (current_token != last_token)
	{
		token = current_token->content;
		if (token->type & T_REDIRECT_HEREDOC)
		{
			ms->current_heredoc = ms->current_heredoc->next;
			current_token = current_token->next;
		}
		current_token = current_token->next;
	}
}

static int	add_to_args(t_list **args, t_list **last_node,
		t_token *token, t_minishell *ms)
{
	t_list		**last_arg;
	int			is_empty;
	char *const	dup = ft_strdup(token->data);

	if (*args == NULL)
		last_arg = args;
	else
		last_arg = last_node;
	is_empty = 0;
	if (dup != NULL)
	{
		unquote(dup, NO_QUOTE);
		is_empty = dup[0] == '\0';
		free(dup);
	}
	parse_token(token, ms->envl, ms->last_exit_status, 0);
	if ((is_empty || *token->data != '\0') && add_to_list(last_arg, token))
	{
		ft_lstclear(args, NULL);
		return (1);
	}
	*last_node = ft_lstlast(*last_arg);
	return (0);
}
