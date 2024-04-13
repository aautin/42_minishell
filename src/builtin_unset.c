/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:56:32 by aautin            #+#    #+#             */
/*   Updated: 2024/04/13 16:13:07 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "getenv.h"

int	builtin_unset(t_list **envp, const char key[])
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
