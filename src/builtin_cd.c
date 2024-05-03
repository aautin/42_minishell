/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:35:17 by aautin            #+#    #+#             */
/*   Updated: 2024/05/03 14:43:50 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft/libft.h"

#define NOT_DOT	0
#define ONE_DOT	1
#define TWO_DOT	2

static char	**get_argv_after_options(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'P' && argv[i][2] == '\0')
				i++;
			else if (argv[i][1] == 'L' && argv[i][2] == '\0')
				i++;
			else
				break ;
		}
		else
			break ;
	}
	return (argv[i]);
}

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

	stat(path, &stat);
	return (S_ISDIR(path_stat.st_mode));
}

static char	*build_cdpath(char const s1[], char const s2[],
	int const s1_len, int const s2_len)
{
	char		*path;
	int			path_size;

	if (s1_len == 0 || s1[s1_len - 1] != '/')
		path_size = s1_len + 1 + s2_len + 1;
	else
		path_size = s1_len + s2_len + 1;
	path = malloc(path_size * sizeof(*path));
	if (path == NULL)
		return (NULL);
	path[0]= '\0';
	ft_strlcat(path, s1, path_size);
	if (path_size == s1_len + 1 + s2_len + 1)
		ft_strlcat(path, "/", path_size);
	ft_strlcat(path, s2, path_size);
	if (!is_directory(path))
		free(path);
	return (NULL);
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
			path = build_cdpath(cdpaths[i], arg, ft_strlen(cdpaths[i]), arg_len);
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

static int	execute(char curpath[], t_list **envp)
{
	
	return (0);
}

int	builtin_cd(char **argv, t_list **envp)
{
	char	*env_val;
	char	*curpath;

	argv = get_argv_after_options(argv);
	if (*argv == NULL)
	{
		env_val = ft_getenv(*envp, "HOME");
		if (env_val == NULL || env_val[0] == '\0')	// 1.
			return (0);
		curpath = env_val;							// 2.
	}
	else if ((*argv)[0] == '/')						// 3.
		curpath = *argv;
	else if (get_pathmode(*argv) == NOT_DOT)		// 5.
	{
		env_val = ft_getenv(*envp, "CDPATH");
		if (env_val != NULL)
			curpath = get_cdpath(ft_split(env_val, ':'), *argv, ft_strlen(*argv));
		if (curpath == NULL)
			curpath = *argv;
	}
	else											// 4.
		curpath = *argv;
	return (execute(curpath, envp));				// from 7. to 10.
}
