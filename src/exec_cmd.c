/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:01:03 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 20:14:19 by pnguyen-         ###   ########.fr       */
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
#include "utils.h"

#define NOT_FOUND_MSG ": command not found\n"
#define NOT_FOUND_CODE 127
#define NO_ACCESS_CODE 126

static char	**liststr_to_tabstr(t_list *current);
static int	execute_cmd(char const pathname[], char **argv, t_list *envp);

int	prepare_cmd(char **argv, t_list **envl)
{
	char	**paths;
	char	*pathname;
	int		exit_code;

	if (argv[0] == NULL || argv[0][0] == '\0')
		return (0);
	if (is_a_builtin(argv[0]))
		return (execute_builtin(argv, envl));
	paths = get_paths(*envl);
	pathname = check_exec(argv[0], paths, F_OK | X_OK);
	if (pathname == NULL)
		pathname = check_exec(argv[0], paths, F_OK);
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
	exit_code = execute_cmd(pathname, argv, *envl);
	free(pathname);
	return (exit_code);
}

static char	**liststr_to_tabstr(t_list *current)
{
	int				i;
	int const		size = ft_lstsize(current);
	char **const	tab = malloc((size + 1) * sizeof(char *));

	if (tab == NULL)
	{
		perror("liststr_to_tabstr():malloc()");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		tab[i] = current->content;
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static int	execute_cmd(char const pathname[], char **argv, t_list *envp)
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
