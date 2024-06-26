/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:45:36 by aautin            #+#    #+#             */
/*   Updated: 2024/05/18 20:37:55 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

int	builtin_env(t_list *envp)
{
	size_t	content_len;

	while (envp)
	{
		content_len = ft_strlen(envp->content);
		if (write(1, envp->content, content_len) == -1)
		{
			perror("builtin_env():write()");
			return (1);
		}
		write(1, "\n", 1);
		envp = envp->next;
	}
	return (0);
}
