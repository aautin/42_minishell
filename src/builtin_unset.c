/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:56:32 by aautin            #+#    #+#             */
/*   Updated: 2024/05/01 18:28:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "getenv.h"
#include "getenv_utils.h"

int	builtin_unset(char **argv, t_list **envp)
{
	t_list	*node;
	t_list	*prev;
	char	*value;
	char	*key;
	int		key_size;

	while (*(++argv))
	{
		value = ft_getenv(*envp, *argv);
		if (value == NULL)
			continue ;
		key = value - (ft_strlen(*argv) + 1);
		key_size = ft_strlen(key) + 1;
		node = *envp;
		prev = node;
		while (node)
		{
			if (ft_strncmp(node->content, key, key_size) == 0)
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
