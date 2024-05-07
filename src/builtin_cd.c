/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:35:17 by aautin            #+#    #+#             */
/*   Updated: 2024/05/07 20:38:50 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
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
	char* const	path = malloc(path_size * sizeof(*path));

	if (path == NULL)
		return (NULL);
	path[0]= '\0';
	ft_strlcat(path, s1, path_size);
	if (path_size == s1_len + 1 + s2_len + 1)
		ft_strlcat(path, "/", path_size);
	ft_strlcat(path, s2, path_size);
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
			{
				if (is_directory(path))
					break ;
				else
					free(path);
			}
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
	int		path_size;

	path_size = 1;	// '\0'
	i = 0;
	while (components[i])
	{
		path_size += ft_strlen(components[i]); // the component
		path_size += (components[i++][0] != '\0'); // the '/' if component's not empty
	}
	path_size += (path_size == 1);	// root path : just '/'
	path = malloc(path_size * sizeof(*path));
	if (path == NULL)
		return (ft_freeall(components), perror("components_to_path():malloc()"), NULL);
	path[0] = '/';
	path[1] = '\0';
	i = 0;
	while (components[i])
	{
		ft_strlcat(path, components[i], path_size);
		if (components[i++][0] != '\0')
			ft_strlcat(path, "/", path_size);
	}
	path[path_size - 1] = '\0'; 
	return (ft_freeall(components), path);
}

static void	go_previous_dir(char **components, int twodot_index)
{
	components[twodot_index--][0] = '\0';
	while (twodot_index + 1 && components[twodot_index][0] == '\0')
		twodot_index--;
	if (twodot_index >= 0)
		components[twodot_index][0] = '\0';
}

static char	*component_conversion(char abs_path[])
{
	int		i;
	char	**path_components;

	// printf("%p\n", abs_path);
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
	printf("path components:\n");
	i = 0;
	while (path_components[i] != NULL)
		printf("%s\n", path_components[i++]);
	return (components_to_path(path_components));
}

static int	execute(char curpath[], t_list **envp, char dir_operand)
{
	char const	*pwd = ft_getenv(*envp, "PWD");
	char		*absolute_path;

	if (*curpath != '/' && pwd)							// 7.
		absolute_path = build_path(pwd, curpath, ft_strlen(pwd), ft_strlen(curpath));
	else if (*curpath != '/' && !pwd)
		return (free(curpath), 0);
	else if (*curpath == '/' || absolute_path == NULL)
		absolute_path = ft_strdup(curpath);
	free(curpath);
	absolute_path = component_conversion(absolute_path);	// 8.
	if (absolute_path == NULL)
		return (1);
	if (ft_strlen(absolute_path) + 1 > PATH_MAX && ft_strlen(dir_operand) + 1 <= PATH_MAX)	// 9.
	{
		if (pwd && ft_strnstr(absolute_path, pwd, ft_strlen(absolute_path)) != NULL)
			absolute_path = find_subpath();
		else
			return (free(absolute_path), 0);
	}
	//chdir
	return (free(absolute_path), 0);
}

int	builtin_cd(char **argv, t_list **envp)
{
	char	*env_val;
	char	*curpath;

	curpath = NULL;
	if (argv[1] != NULL && argv[2] != NULL)
		return (write(STDERR_FILENO, TOO_MANY_ARGS, ft_strlen(TOO_MANY_ARGS)), 1);
	if (argv[1] == NULL)
	{
		env_val = ft_getenv(*envp, "HOME");
		if (env_val == NULL || env_val[0] == '\0')	// 1.
			return (0);
		curpath = ft_strdup(env_val);							// 2.
	}
	else if (get_pathmode(argv[1]) == NOT_DOT && argv[1][0] != '/') // 5.
	{
		env_val = ft_getenv(*envp, "CDPATH");
		if (env_val != NULL)
			curpath = get_cdpath(ft_split(env_val, ':'), argv[1], ft_strlen(argv[1]));
		if (curpath == NULL)
			curpath = ft_strdup(argv[1]);
	}
	else											// 3. and 4.
		curpath = ft_strdup(argv[1]);
	return (execute(curpath, envp, argv[1]));				// from 7. to 10.
}
