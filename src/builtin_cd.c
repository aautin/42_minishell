/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:35:17 by aautin            #+#    #+#             */
/*   Updated: 2024/05/21 14:11:17 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "getenv.h"
#include "getenv_utils.h"
#include "builtin_cd.h"

#define STDERR			STDERR_FILENO
#define TOO_MANY_ARGS	"builtin_cd(): too many arguments\n"
#define TOO_LONG_PATH	"builtin_cd(): path given is too long\n"

static char	*comp_path(char **components)
{
	int		i;
	char	*path;
	size_t	path_size;

	path_size = 1;
	i = 0;
	while (components[i] != NULL)
	{
		path_size += ft_strlen(components[i]);
		path_size += (components[i++][0] != '\0');
	}
	path_size += (path_size == 1);
	path = malloc(path_size * sizeof(*path));
	if (path == NULL)
		return (ft_freeall(components), perror("comp_path():malloc()"), NULL);
	path[0] = '/';
	path[1] = '\0';
	i = 0;
	while (components[i] != NULL)
	{
		ft_strlcat(path, components[i], path_size);
		if (components[i++][0] != '\0')
			ft_strlcat(path, "/", path_size);
	}
	return (path[path_size - 1] = '\0', ft_freeall(components), path);
}

static char	*component_conversion(char abs_path[])
{
	int		i;
	char	**path_components;

	path_components = ft_split(abs_path, '/');
	free(abs_path);
	if (path_components == NULL)
		return (perror("component_conversion():ft_split()"), NULL);
	i = 0;
	while (path_components[i] != NULL)
	{
		if (get_pathmode(path_components[i]) == ONE_DOT)
			path_components[i][0] = '\0';
		else if (get_pathmode(path_components[i]) == TWO_DOT)
			go_previous_dir(path_components, i);
		i++;
	}
	return (comp_path(path_components));
}

static int	execute(char curpath[], t_list **envp)
{
	char	*abs_path;

	if (curpath == NULL)
		return (perror("builtin_cd():ft_strdup()"), 1);
	if (*curpath != '/')
		return (change_directory(envp, curpath));
	abs_path = ft_strdup(curpath);
	free(curpath);
	abs_path = component_conversion(abs_path);
	if (abs_path == NULL)
		return (1);
	if (ft_strlen(abs_path) + 1 > PATH_MAX)
	{
		write(STDERR, TOO_LONG_PATH, ft_strlen(TOO_LONG_PATH));
		return (free(abs_path), 1);
	}
	return (change_directory(envp, abs_path));
}

int	builtin_cd(char **argv, t_list **envp)
{
	char	*env_val;
	char	*curpath;

	curpath = NULL;
	if (argv[1] != NULL && argv[2] != NULL)
		return (write(STDERR, TOO_MANY_ARGS, ft_strlen(TOO_MANY_ARGS)), 1);
	if (argv[1] == NULL)
	{
		env_val = ft_getenv(*envp, "HOME");
		if (env_val == NULL || env_val[0] == '\0')
			return (0);
		curpath = ft_strdup(env_val);
	}
	else if (get_pathmode(argv[1]) == NOT_DOT && argv[1][0] != '/')
	{
		env_val = ft_getenv(*envp, "CDPATH");
		if (env_val != NULL)
			curpath = get_cdpath(ft_split(env_val, ':'), argv[1],
					ft_strlen(argv[1]));
		if (curpath == NULL)
			curpath = ft_strdup(argv[1]);
	}
	else
		curpath = ft_strdup(argv[1]);
	return (execute(curpath, envp));
}
