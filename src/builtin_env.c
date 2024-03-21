/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:45:36 by aautin            #+#    #+#             */
/*   Updated: 2024/03/21 17:09:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft/libft.h"

#include "builtin_env.h"

int	builtin_env(t_list *envp)
{
	if (envp == NULL)
		return (1);
	else
	{
		while (envp)
		{
			printf("%s\n", (char *)envp->content);
			envp = envp->next;
		}
		return (0);
	}
}
