/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:03:01 by aautin            #+#    #+#             */
/*   Updated: 2024/04/13 19:11:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

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

int	builtin_export(t_list *envp, const char *) {
	
}
