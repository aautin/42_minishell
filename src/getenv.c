/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:51:00 by aautin            #+#    #+#             */
/*   Updated: 2024/03/19 14:18:16 by aautin           ###   ########.fr       */
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

void	remove_env(t_list **envp, t_list *head, char *to_find)
{
	t_list	*previous;
	t_list	*current;
	char	*str;

	str = ft_getenv(*envp, to_find) - ft_strlen(to_find) - 1;
	previous = *envp;
	current = (*envp)->next;
	if (!ft_strncmp(((char *)(*envp)->content), str, ft_strlen(str)))
	{
		ft_lstdelone(previous, &free);
		*envp = current;
		return ;
	}
	while (current)
	{
		if (!ft_strncmp(((char *)current->content), str, ft_strlen(str)))
		{
			head = current->next;
			ft_lstdelone(current, &free);
			previous->next = head;
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	modify_env(t_list *envp, char *to_find, char *result)
{
	char	*content;
	char	*new_content;

	content = ft_getenv(envp, to_find) - ft_strlen(to_find) - 1;
	while (envp)
	{
		if (!ft_strncmp(((char *)envp->content), content, ft_strlen(content)))
		{
			free(envp->content);
			new_content = malloc((ft_strlen(to_find) + ft_strlen(result) + 2)
					* sizeof(char));
			if (new_content == NULL)
				return (1);
			new_content[0] = 0;
			ft_strlcat(new_content, to_find,
				ft_strlen(to_find) + ft_strlen(result) + 2);
			ft_strlcat(new_content, "=",
				ft_strlen(to_find) + ft_strlen(result) + 2);
			ft_strlcat(new_content, result,
				ft_strlen(to_find) + ft_strlen(result) + 2);
			return (envp->content = new_content, 0);
		}
		envp = envp->next;
	}
	return (-1);
}
