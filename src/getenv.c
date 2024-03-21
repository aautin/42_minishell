/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:51:00 by aautin            #+#    #+#             */
/*   Updated: 2024/03/21 16:37:15 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "getenv_utils.h"

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

int	remove_env(t_list **envp, const char key[])
{
	t_list	*node;
	char	*value;
	int		value_len;

	value = ft_getenv(*envp, key);
	if (value == NULL)
		return (1);
	value -= ft_strlen(key) + 1;
	value_len = ft_strlen(value);
	node = *envp;
	if (!ft_strncmp(((char *)node->content), value, value_len))
	{
		ft_remove(envp, node, node);
		return (0);
	}
	while (node->next)
	{
		if (!ft_strncmp(((char *)node->next->content), value, value_len))
		{
			ft_remove(envp, node, node->next);
			return (0);
		}
		node = node->next;
	}
	return (1);
}

int	modify_env(t_list *envp, const char key[], const char new_value[])
{
	char	*value;
	int		key_len;

	value = ft_getenv(envp, key);
	if (value == NULL)
		return (1);
	key_len = ft_strlen(key);
	value -= key_len + 1;
	while (envp)
	{
		if (!ft_strncmp(((char *)envp->content), value, key_len + 1))
		{
			if (modify(envp, key, new_value))
				return (2);
			return (0);
		}
		envp = envp->next;
	}
	return (1);
}
