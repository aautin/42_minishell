/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:37:47 by aautin            #+#    #+#             */
/*   Updated: 2024/05/15 17:07:53 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

void	remove_env(t_list **head, t_list *prev, t_list *cur)
{
	if (*head == cur)
	{
		*head = cur->next;
		ft_lstdelone(cur, &free);
	}
	else
	{
		prev->next = cur->next;
		ft_lstdelone(cur, &free);
	}
}

int	modify_env(t_list *envp, char const key[], char const new_value[])
{
	char	*new_content;
	int		new_content_len;

	if (new_value == NULL)
		new_value = "";
	free(envp->content);
	new_content_len = ft_strlen(key) + ft_strlen(new_value) + 2;
	new_content = ft_calloc(new_content_len, sizeof(char));
	if (new_content == NULL)
	{
		perror("modify():ft_calloc()");
		return (1);
	}
	new_content[0] = '\0';
	ft_strlcat(new_content, key, new_content_len);
	ft_strlcat(new_content, "=", new_content_len);
	ft_strlcat(new_content, new_value, new_content_len);
	envp->content = new_content;
	return (0);
}

int	add_env(t_list **envp, char const key[], char const value[])
{
	int		content_size;
	char	*content;
	t_list	*new_node;

	if (value == NULL)
		value = "";
	content_size = ft_strlen(key) + 1 + ft_strlen(value) + 1;
	content = malloc(content_size * sizeof(char));
	new_node = ft_lstnew(content);
	if (content == NULL || new_node == NULL)
	{
		perror("add_env():malloc()");
		free(content);
		free(new_node);
		return (1);
	}
	content[0] = '\0';
	ft_strlcat(content, key, content_size);	
	ft_strlcat(content, "=", content_size);	
	ft_strlcat(content, value, content_size);
	ft_lstadd_front(envp, new_node);
	return (0);
}
