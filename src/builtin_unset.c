/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:56:32 by aautin            #+#    #+#             */
/*   Updated: 2024/05/17 18:05:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "getenv.h"
#include "getenv_utils.h"

static void	find_and_unset(char const arg[], t_list **envp, char const value[])
{
	t_list		*node;
	t_list		*prev;
	char const	*key;
	size_t		key_size;

	key = value - (ft_strlen(arg) + 1);
	key_size = ft_strlen(key) + 1;
	node = *envp;
	prev = node;
	while (node != NULL)
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

int	builtin_unset(char **argv, t_list **envp)
{
	char	*value;

	while (*(++argv) != NULL)
	{
		value = ft_getenv(*envp, *argv);
		if (value == NULL)
			continue ;
		find_and_unset(*argv, envp, value);
	}
	return (0);
}
