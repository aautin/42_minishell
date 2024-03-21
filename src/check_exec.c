/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:07:57 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 20:41:20 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

static char	*join_path(char const path[], char const exec_name[]);

char	*check_exec(char const exec_name[], char **paths, int mode)
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
		return ((char *)exec_name);
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

