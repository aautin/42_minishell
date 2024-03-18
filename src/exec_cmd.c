/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:01:03 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 21:09:14 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#define NOT_FOUND_MSG ": command not found\n"
#define NOT_FOUND_CODE 127
#define NO_ACCESS_CODE 126

static char	**get_paths(char **envp);
static void	my_perror(char const name[], char const msg[]);
static char	*join_path(char path[], char exec_name[]);
static char	*check_exec(char exec_name[], char **paths, int mode);

//static int	do_thing(char **argv, char **envp)
//{
//	return (0);
//}

int	exec_prog(char **argv, char **envp)
{
	char	**paths;
	char	*pathname;
	int		exit_code;

	if (argv[0] == NULL || argv[0][0] == '\0')
		return (0);
//	if (is_a_builtin(argv[0]))
//		return (do_thing(argv, envp));
	paths = get_paths(envp);
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
	execve(pathname, argv, envp);
	if (errno == EACCES)
		exit_code = NO_ACCESS_CODE;
	else
		exit_code = EXIT_FAILURE;
	perror(pathname);
	free(pathname);
	return (exit_code);
}

static void	my_perror(char const name[], char const msg[])
{
	char	*full_msg;

	full_msg = ft_strjoin(name, msg);
	if (full_msg == NULL)
	{
		perror("my_perror():ft_strjoin()");
		return ;
	}
	ft_putstr_fd(full_msg, STDERR_FILENO);
	free(full_msg);
}

static char	*check_exec(char exec_name[], char **paths, int mode)
{
	int		i;
	char	*pathname;

	if (ft_strchr(exec_name, '/') != NULL)
	{
		if (access(exec_name, mode) == -1)
			return (NULL);
		exec_name = ft_strdup(exec_name);
		if (exec_name == NULL)
			perror("check_cmd():ft_strdup()");
		return (exec_name);
	}
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		pathname = join_path(paths[i], exec_name);
		if (pathname == NULL || access(pathname, mode) != -1)
			return (pathname);
		free(pathname);
		i++;
	}
	return (NULL);
}

static char	**get_paths(char **envp)
{
	char	**paths;

	if (envp == NULL)
		return (NULL);
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (*envp == NULL)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (paths == NULL)
		perror("get_paths():ft_split()");
	return (paths);
}

static char	*join_path(char path[], char exec_name[])
{
	size_t	len_path;
	size_t	len_cmd;
	char	*pathname;

	len_path = ft_strlen(path);
	len_cmd = ft_strlen(exec_name);
	pathname = malloc((len_path + 1 + len_cmd + 1) * sizeof(char));
	if (pathname == NULL)
	{
		perror("join_path():malloc()");
		return (NULL);
	}
	pathname[len_path + 1 + len_cmd] = '\0';
	ft_memcpy(pathname, path, len_path);
	pathname[len_path] = '/';
	ft_memcpy(pathname + len_path + 1, exec_name, len_cmd);
	return (pathname);
}
