/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:07:57 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/29 20:09:47 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft/libft.h"

#define ERROR_MSG_DIR	": Is a directory\n"

void		my_perror(char const name[], char const msg[]);
void		file_perror(char const name[]);
static char	*join_path(char const path[], char const exec_name[]);
static char	*find_cmd(char const exec_name[], char *const *paths);

char	*check_exec(char const exec_name[], char *const *paths)
{
	char	*pathname;

	if (ft_strchr(exec_name, '/') != NULL)
	{
		if (access(exec_name, F_OK) == -1)
			return (NULL);
		pathname = ft_strdup(exec_name);
		if (pathname == NULL)
			perror("check_cmd():ft_strdup()");
		return (pathname);
	}
	if (paths == NULL)
		return (NULL);
	return (find_cmd(exec_name, paths));
}

void	my_perror(char const name[], char const msg[])
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

void	file_perror(char const name[])
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

static char	*find_cmd(char const exec_name[], char *const *paths)
{
	int		i;
	char	*pathname;
	char	*second_chance;

	i = 0;
	second_chance = NULL;
	while (paths[i] != NULL)
	{
		pathname = join_path(paths[i], exec_name);
		if (pathname == NULL)
			return (NULL);
		if (access(pathname, F_OK | X_OK) != -1)
			return (pathname);
		if (access(pathname, F_OK) != -1)
		{
			free(second_chance);
			second_chance = pathname;
		}
		else
			free(pathname);
		i++;
	}
	return (second_chance);
}

static char	*join_path(char const path[], char const exec_name[])
{
	size_t const	len_path = ft_strlen(path);
	size_t const	len_cmd = ft_strlen(exec_name);
	char *const		pathname
		= malloc((len_path + 1 + len_cmd + 1) * sizeof(char));

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
