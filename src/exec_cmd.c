/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:01:03 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/10 20:20:24 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft/libft.h"

#include "builtin.h"
#include "check_exec.h"
#include "minishell.h"

#define NOT_FOUND_MSG	": command not found\n"
#define ERROR_MSG_DIR	": Is a directory\n"
#define NOT_FOUND_CODE	127
#define NO_ACCESS_CODE	126
#define I_AM_A_CHILD	1

static char	**liststr_to_tabstr(t_list *envl);
static int	execute_cmd(char const pathname[], char **argv, t_list *envp);
static void	file_perror(char const name[]);
static void	my_perror(char const name[], char const msg[]);

int	prepare_cmd(t_minishell *ms, char **argv)
{
	char	*pathname;
	int		exit_code;

	if (argv[0] == NULL)
		return (0);
	if (is_a_builtin(argv[0]))
		return (execute_builtin(ms, argv, I_AM_A_CHILD, NULL));
	pathname = check_exec(argv[0], ms->envl);
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
	file_perror(pathname);
	free(envp);
	return (exit_code);
}

static void	my_perror(char const name[], char const msg[])
{
	char *const	full_msg = ft_strjoin(name, msg);

	if (full_msg == NULL)
	{
		perror("my_perror():ft_strjoin()");
		return ;
	}
	ft_putstr_fd(full_msg, STDERR_FILENO);
	free(full_msg);
}

static void	file_perror(char const name[])
{
	struct stat	sb;
	int const	errsv = errno;

	if (stat(name, &sb) == -1)
	{
		perror(name);
		return ;
	}
	if (S_ISDIR(sb.st_mode))
		my_perror(name, ERROR_MSG_DIR);
	else
	{
		errno = errsv;
		perror(name);
	}
}
