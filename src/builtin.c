/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:37:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/11 20:36:03 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "builtins.h"
#include "minishell.h"

#define ECHO_BUILTIN	"echo"
#define CD_BUILTIN		"cd"
#define PWD_BUILTIN		"pwd"
#define EXPORT_BUILTIN	"export"
#define UNSET_BUILTIN	"unset"
#define ENV_BUILTIN		"env"
#define EXIT_BUILTIN	"exit"

int	execute_builtin(t_minishell *ms, char **argv, int is_child, int const fd[3])
{
	size_t	size_cmd;

	if (argv[0] == NULL)
		return (0);
	size_cmd = ft_strlen(argv[0]) + 1;
	if (ft_strncmp(argv[0], ECHO_BUILTIN, size_cmd) == 0)
		return (builtin_echo(argv));
	if (ft_strncmp(argv[0], PWD_BUILTIN, size_cmd) == 0)
		return (builtin_pwd());
	if (ft_strncmp(argv[0], EXPORT_BUILTIN, size_cmd) == 0)
		return (builtin_export(argv, &ms->envl));
	if (ft_strncmp(argv[0], UNSET_BUILTIN, size_cmd) == 0)
		return (builtin_unset(argv, &ms->envl));
	if (ft_strncmp(argv[0], ENV_BUILTIN, size_cmd) == 0)
		return (builtin_env(ms->envl));
	if (ft_strncmp(argv[0], EXIT_BUILTIN, size_cmd) == 0)
		return (builtin_exit(argv, ms, is_child, fd));
	if (ft_strncmp(argv[0], CD_BUILTIN, size_cmd) == 0)
		return (builtin_cd(argv, &ms->envl));
	return (1);
}

int	is_a_builtin(char const cmd[])
{
	size_t				i;
	size_t				size_cmd;
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
	size_cmd = ft_strlen(cmd) + 1;
	i = 0;
	while (i < size_builtin)
	{
		if (ft_strncmp(cmd, builtin_names[i], size_cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}
