/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:51:00 by aautin            #+#    #+#             */
/*   Updated: 2024/03/18 19:11:24 by aautin           ###   ########.fr       */
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
		env_copy = ft_strdup((const char *) *envp);
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

char	*ft_getenv(t_list *envp, char *to_find)
{
	char	*temp;

	while (envp)
	{
		temp = ft_strchr((char *) envp->content, '=');
		if (temp == NULL)
			return (NULL);
		*temp = '\0';
		if (ft_strncmp(to_find, (char *) envp->content,
				ft_strlen((char *) envp->content)) == 0)
		{
			*temp = '=';
			return (temp + 1);
		}
		*temp = '=';
		envp = envp->next;
	}
	return (NULL);
}

void	remove_env(t_list **envp, char *to_find)
{
	t_list	*head;
	t_list	*node;
	char	*str;

	str = ft_strchr((char *) (*envp)->content, '=');
	*str = '\0';

	head = *envp;
	while (*envp)
	{
		str = ft_strchr((char *) (*envp)->content, '=');
		*str = '\0';
		if (ft_strncmp(to_find, (char *) (*envp)->content,
				ft_strlen((char *) (*envp)->content)) == 0)
		{
			if (*envp == head)
			{
				node = *envp;
				head = (*envp)->next;
				ft_lstdelone(node, &free);
			}
			else
			{
				node = *envp;
				 = (*envp)->next;
				ft_lstdelone(node, &free);
			}
			return ;
		}
		*str = '=';
		*envp = (*envp)->next;
	}
	*envp = head;
}
