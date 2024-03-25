/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:37:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 19:30:41 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "minishell.h"

int	execute_builtin(t_minishell *ms, char **argv)
{
	(void)ms;
	size_t len_cmd;

	if (argv[0] == NULL)
		return (0);
	len_cmd = ft_strlen(argv[0]);
	return (1);
}

int	is_a_builtin(char const cmd[])
{
	char const *const	builtin_names[] = {"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL};
	int					i;
	size_t				len;

	if (cmd == NULL)
		return (1);
	len = ft_strlen(cmd);
	i = 0;
	while (builtin_names[i] != NULL)
	{
		if (ft_strncmp(cmd, builtin_names[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}
