/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:56:02 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/17 20:02:30 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"

int	add_to_list(t_list **list, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (node == NULL)
	{
		perror("add_to_list():ft_lstnew()");
		return (1);
	}
	ft_lstadd_back(list, node);
	return (0);
}

void	free_heredoc(void *content)
{
	char *const	filename = content;

	if (filename == NULL)
		return ;
	if (unlink(filename) == -1)
		perror(filename);
	free(filename);
}

void	free_token(void *content)
{
	t_token *const	token = content;

	free(token->data);
	free(token);
}
