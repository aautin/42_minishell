/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:37:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 20:59:08 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "builtin_echo.h"

int	execute_builtin(char **argv, t_list **envl)
{
	(void)argv;
	(void)envl;
	size_t const	len_cmd = ft_strlen(argv[0]);
	if (ft_strncmp(argv[0], "echo", len_cmd) == 0)
		return (builtin_echo(argv));
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

	if (cmd == NULL || *cmd == '\0')
		return (0);
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
