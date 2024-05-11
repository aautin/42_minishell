/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:51:00 by aautin            #+#    #+#             */
/*   Updated: 2024/05/11 20:24:51 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

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

t_list	*find_env(t_list *envp, char const key[])
{
	size_t const	key_size = ft_strlen(key) + 1;
	char			*ptr;

	while (envp)
	{
		ptr = ft_strchr(envp->content, '=');
		if (ptr == NULL)
			continue ;
		*ptr = '\0';
		if (ft_strncmp(key, envp->content, key_size) == 0)
			break ;
		*ptr = '=';
		envp = envp->next;
	}
	return (envp);
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
			continue ;
		*temp = '\0';
		if (ft_strncmp(key, content, ft_strlen(content) + 1) == 0)
		{
			*temp = '=';
			return (temp + 1);
		}
		*temp = '=';
		envp = envp->next;
	}
	return (NULL);
}
