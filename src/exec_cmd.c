/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:01:03 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 19:13:05 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "builtin.h"
#include "check_exec.h"
#include "getenv.h"
#include "minishell.h"
#include "utils.h"

#define NOT_FOUND_MSG	": command not found\n"
#define NOT_FOUND_CODE	127
#define NO_ACCESS_CODE	126

static char	**get_paths(t_list *envl);
static char	**liststr_to_tabstr(t_list *envl);
static int	execute_cmd(char const pathname[], char **argv, t_list *envp);

int	prepare_cmd(t_minishell *ms, char **argv)
{
	char	**paths;
	char	*pathname;
	int		exit_code;

	if (argv[0] == NULL)
		return (0);
	if (is_a_builtin(argv[0]))
		return (execute_builtin(ms, argv));
	paths = get_paths(ms->envl);
	pathname = check_exec(argv[0], paths);
	if (paths != NULL)
		ft_freeall(paths);
	if (pathname == NULL)
	{
		if (ft_strchr(argv[0], '/') != NULL)
			perror(argv[0]);
		else
			my_perror(argv[0], NOT_FOUND_MSG);
		return (NOT_FOUND_CODE);
	}
	exit_code = execute_cmd(pathname, argv, ms->envl);
	free(pathname);
	return (exit_code);
}

static char	**get_paths(t_list *envl)
{
	char *const	env_path = ft_getenv(envl, "PATH");
	char		**paths;

	if (env_path == NULL)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (paths == NULL)
		perror("get_paths():ft_split()");
	return (paths);
}

static char	**liststr_to_tabstr(t_list *envl)
{
	int				i;
	int const		size = ft_lstsize(envl);
	char **const	tab = malloc((size + 1) * sizeof(char *));

	if (tab == NULL)
	{
		perror("liststr_to_tabstr():malloc()");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		tab[i] = envl->content;
		envl = envl->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static int	execute_cmd(char const pathname[], char **argv, t_list *envl)
{
	int				exit_code;
	char **const	envp = liststr_to_tabstr(envl);

	execve(pathname, argv, envp);
	if (errno == EACCES)
		exit_code = NO_ACCESS_CODE;
	else
		exit_code = EXIT_FAILURE;
	perror(pathname);
	free(envp);
	return (exit_code);
}
