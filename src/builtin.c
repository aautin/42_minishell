/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:37:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 20:31:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "builtin_echo.h"
#include "minishell.h"

#define ECHO_BUILTIN	"echo"
#define CD_BUILTIN		"cd"
#define PWD_BUILTIN		"pwd"
#define EXPORT_BUILTIN	"export"
#define UNSET_BUILTIN	"unset"
#define ENV_BUILTIN		"env"
#define EXIT_BUILTIN	"exit"

int	execute_builtin(t_minishell *ms, char **argv)
{
	(void)ms;
	size_t	len_cmd;

	if (argv[0] == NULL)
		return (0);
	len_cmd = ft_strlen(argv[0]);
	if (ft_strncmp(argv[0], ECHO_BUILTIN, len_cmd) == 0)
		return (builtin_echo(argv));
	return (1);
}

int	is_a_builtin(char const cmd[])
{
	size_t				i;
	size_t				len;
	char const *const	builtin_names[] = {
		ECHO_BUILTIN,
		CD_BUILTIN,
		PWD_BUILTIN,
		EXPORT_BUILTIN,
		UNSET_BUILTIN,
		ENV_BUILTIN,
		EXIT_BUILTIN,
	};
	size_t const		size_builtin = sizeof(builtin_names)
		/ sizeof(*builtin_names);

	if (cmd == NULL)
		return (1);
	len = ft_strlen(cmd);
	i = 0;
	while (i < size_builtin)
	{
		if (ft_strncmp(cmd, builtin_names[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}
