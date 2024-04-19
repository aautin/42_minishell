/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:51:00 by aautin            #+#    #+#             */
/*   Updated: 2024/04/19 20:40:39 by aautin           ###   ########.fr       */
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

int	modify(t_list *envp, const char key[], const char new_value[])
{
	char	*new_content;
	int		new_content_len;

	free(envp->content);
	new_content_len = ft_strlen(key) + ft_strlen(new_value) + 2;
	new_content = ft_calloc(new_content_len, sizeof(char));
	if (new_content == NULL)
	{
		perror("modify():ft_calloc()");
		return (1);
	}
	ft_strlcat(new_content, key, new_content_len);
	ft_strlcat(new_content, "=", new_content_len);
	ft_strlcat(new_content, new_value, new_content_len);
	envp->content = new_content;
	return (0);
}

t_list	*create_env(char **envp)
{
	t_list	*new_envp;
	t_list	*new_node;
	char	*env_copy;

	new_envp = NULL;
	while (*envp)
	{
		env_copy = ft_strdup(*envp);
		if (env_copy == NULL)
		{
			ft_lstclear(&new_envp, &free);
			return (perror("create_env():ft_strdup()"), NULL);
		}
		new_node = ft_lstnew(env_copy);
		if (new_node == NULL)
		{
			free(env_copy);
			ft_lstclear(&new_envp, &free);
			perror("create_env():ft_lstnew()");
			return (NULL);
		}
		ft_lstadd_back(&new_envp, new_node);
		envp++;
	}
	return (new_envp);
}

char	*ft_getenv(t_list *envp, const char key[])
{
	char	*temp;
	char	*content;

	while (envp)
	{
		content = (char *) envp->content;
		temp = ft_strchr(content, '=');
		if (temp == NULL)
			return (NULL);
		*temp = '\0';
		if (ft_strncmp(key, content, ft_strlen(content)) == 0)
		{
			*temp = '=';
			return (temp + 1);
		}
		*temp = '=';
		envp = envp->next;
	}
	return (NULL);
}
