/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:35:17 by aautin            #+#    #+#             */
/*   Updated: 2024/05/05 19:34:15 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft/libft.h"

#include "getenv.h"

#define	TOO_MANY_ARGS "cd: too many arguments\n"

#define NOT_DOT	0
#define ONE_DOT	1
#define TWO_DOT	2

static int	get_pathmode(char const arg[])
{
	if (arg[0] == '.' && arg[1] == '.' && (arg[2] == '/' || arg[2] == '\0'))
		return (TWO_DOT);
	if (arg[0] == '.' && (arg[1] == '/' || arg[1] == '\0'))
		return (ONE_DOT);
	return (NOT_DOT);
}

static int	is_directory(char const path[])
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

static char	*build_path(char const s1[], char const s2[],
	int const s1_len, int const s2_len)
{
	int const	path_size = s1_len + (s1_len == 0 || s1[s1_len - 1] != '/') + s2_len + 1;
	char *const	path = malloc(path_size * sizeof(*path));

	if (path == NULL)
		return (NULL);
	path[0]= '\0';
	ft_strlcat(path, s1, path_size);
	if (path_size == s1_len + 1 + s2_len + 1)
		ft_strlcat(path, "/", path_size);
	ft_strlcat(path, s2, path_size);
	if (!is_directory(path))
		return (free(path), NULL);
	return (path);
}

static char	*get_cdpath(char **cdpaths, char const arg[], int const arg_len)
{
	int		i;
	char	*path;

	path = NULL;
	if (cdpaths != NULL)
	{
		i = 0;
		while (cdpaths[i])
		{
			path = build_path(cdpaths[i], arg, ft_strlen(cdpaths[i]), arg_len);
			if (path != NULL)
				break ;
			free(cdpaths[i++]);
		}
		while (cdpaths[i])
			free(cdpaths[i++]);
		free(cdpaths);
	}
	if (path == NULL)
	{
		path = ft_strjoin("./", arg);
		if (!is_directory(path))
			free(path);
	}
	return (path);
}

static char *components_to_path(char **components)
{
	int		i;
	char	*path;
	int		path_len;

	path_len = 1;
	i = 0;
	while (components[i])
	{
		printf("%s|", components[i]);
		i++;
	}
	path = NULL;
	return (path);
}

static char	*component_conversion(char abs_path[])
{
	int		i;
	char	**path_components;

	path_components = ft_split(abs_path, '/');
	if (path_components == NULL)
		return (perror("component_conversion():ft_split()"), NULL);
	free(abs_path);
	i = 0;
	while (path_components[i] != NULL)
	{
		if (get_pathmode(path_components[i]) == ONE_DOT)
			path_components[i][0] = '\0';
		else if (get_pathmode(path_components[i]) == TWO_DOT)
		{
			if (i != 0 && get_pathmode(path_components[i - 1]) != TWO_DOT)
			{
				path_components[i - 1][0] = '\0';
				path_components[i][0] = '\0';
			}
		}
		i++;
	}
	return (components_to_path(path_components));
}

static int	execute(char curpath[], t_list **envp)
{
	char	*pwd;
	char	*absolute_path;

	if (*curpath != '/')							// 7.
	{
		pwd = ft_getenv(*envp, "PWD");
		if (pwd == NULL)
			return (0);
		absolute_path = build_path(pwd, curpath, ft_strlen(pwd), ft_strlen(curpath));
	}
	else
		absolute_path = curpath;
	absolute_path = component_conversion(absolute_path);	// 8.
	if (absolute_path == NULL)
		return (1);
	// change current working directory...
	return (0);
}

int	builtin_cd(char **argv, t_list **envp)
{
	char	*env_val;
	char	*curpath;

	curpath = NULL;
	if (argv[2] != NULL)
		return (write(STDERR_FILENO, TOO_MANY_ARGS, ft_strlen(TOO_MANY_ARGS)), 1);
	if (argv[1] == NULL)
	{
		env_val = ft_getenv(*envp, "HOME");
		if (env_val == NULL || env_val[0] == '\0')	// 1.
			return (0);
		curpath = env_val;							// 2.
	}
	else if (get_pathmode(argv[1]) == NOT_DOT && argv[1][0] != '/') // 5.
	{
		env_val = ft_getenv(*envp, "CDPATH");
		if (env_val != NULL)
			curpath = get_cdpath(ft_split(env_val, ':'), argv[1], ft_strlen(argv[1]));
		if (curpath == NULL)
			curpath = argv[1];
	}
	else											// 3. and 4.
		curpath = argv[1];
	return (execute(curpath, envp));				// from 7. to 10.
}
