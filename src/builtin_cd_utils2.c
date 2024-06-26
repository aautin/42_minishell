/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:00:16 by aautin            #+#    #+#             */
/*   Updated: 2024/05/28 15:48:25 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "libft/libft.h"

#include "builtin_cd.h"

int	get_pathmode(char const arg[])
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

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

static char	*build_path(char const s1[], char const s2[],
	size_t const s1_len, size_t const s2_len)
{
	size_t const	path_size = s1_len + (s1_len == 0 || s1[s1_len - 1] != '/')
		+ s2_len + 1;
	char *const		path = malloc(path_size * sizeof(*path));

	if (path == NULL)
		return (NULL);
	path[0] = '\0';
	ft_strlcat(path, s1, path_size);
	if (path_size == s1_len + 1 + s2_len + 1)
		ft_strlcat(path, "/", path_size);
	ft_strlcat(path, s2, path_size);
	return (path);
}

static void	test_path(char *path[], char const arg[])
{
	if (*path == NULL)
	{
		if (!is_directory(arg))
			*path = NULL;
		else
		{
			*path = ft_strdup(arg);
			if (*path == NULL)
				perror("test_path():ft_strdup()");
		}
	}
}

char	*get_cdpath(char **cdpaths, char const arg[], size_t const arg_len)
{
	int		i;
	char	*path;

	path = NULL;
	if (cdpaths != NULL)
	{
		i = 0;
		while (cdpaths[i] != NULL)
		{
			path = build_path(cdpaths[i], arg, ft_strlen(cdpaths[i]), arg_len);
			if (path != NULL)
			{
				if (is_directory(path))
					break ;
				free(path);
				path = NULL;
			}
			free(cdpaths[i++]);
		}
		while (cdpaths[i] != NULL)
			free(cdpaths[i++]);
		free(cdpaths);
	}
	test_path(&path, arg);
	return (path);
}
