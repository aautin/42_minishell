/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:56:32 by aautin            #+#    #+#             */
/*   Updated: 2024/04/27 17:25:38 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "getenv.h"

int	builtin_unset(char **argv, t_list **envp)
{
	t_list	*node;
	t_list	*prev;
	char	*value;
	char	*key;
	int		key_len;

	while (*(++argv))
	{
		value = ft_getenv(*envp, *argv);
		if (value == NULL)
			continue ;
		key = value - (ft_strlen(*argv) + 1);
		key_len = ft_strlen(key);
		node = *envp;
		prev = node;
		while (node)
		{
			if (ft_strncmp(node->content, key, key_len) == 0)
			{
				remove_env(envp, prev, node);
				break ;
			}
			prev = node;
			node = node->next;
		}
	}
	return (0);
}
