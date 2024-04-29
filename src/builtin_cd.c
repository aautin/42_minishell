/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:35:17 by aautin            #+#    #+#             */
/*   Updated: 2024/04/29 19:49:41 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

#define NOT_DOT		0
#define ONE_DOT		1
#define TWO_DOT		2

static int	get_pathmode(char arg[])
{
	if (arg[0] == '.' && arg[1] == '.')
		return (TWO_DOT);
	if (arg[0] == '.')
		return (ONE_DOT);
	return (NOT_DOT);
}

static char	*build_path(char *first_part, char *second_part)
{
	
}

static char	*get_cdpath(char **cdpaths, char arg[])
{
	int		i;
	char	*path;

	i = 0;
	if (cdpaths == NULL)
		return (NULL);
	while (cdpaths[i])
	{
		path = build_path(cdpaths[i], arg);
		if (path != NULL && access())
		free(cdpaths[i])
		i++;
	}
	while (cdpaths[i])
		free(cdpaths[i++]);
	free(cdpaths);
	return (NULL);
}

static int	execute(char curpath[], t_list **envp)	// from 
{
	
	return (0);
}

int	builtin_cd(char **argv, t_list **envp)
{
	char	*env_val;
	char	*curpath;

	curpath = NULL;
	if (argv[1] == NULL)
	{
		env_val = ft_getenv(*envp, "HOME");
		if (env_val == NULL || env_val[0] == '\0')	// 1.
			return (0);
		curpath = env_val;							// 2.
	}
	else if (argv[1][0] == '/')						// 3.
		curpath = argv[1];
	else if (get_pathmode(argv[1]) == NOT_DOT)		// 5.
	{
		env_val = ft_getenv(*envp, "CDPATH");
		if (env_val != NULL)
			curpath = get_cdpath(ft_split(env_val, ':'), argv[1]);
		if (curpath == NULL)
			curpath = argv[1];
	}
	else											// 4.
		curpath = argv[1];
	return (execute(curpath, envp));
}
