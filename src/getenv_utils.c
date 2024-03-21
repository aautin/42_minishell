/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:51:00 by aautin            #+#    #+#             */
/*   Updated: 2024/03/21 16:34:44 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

void	ft_remove(t_list **head, t_list *prev, t_list *cur)
{
	if (prev == cur)
	{
		*head = prev->next;
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
