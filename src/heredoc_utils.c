/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:07:11 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/17 21:39:19 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#define RANDOM_FILE	"/dev/random"

static char	*get_default_filename(char const delim[]);
static char	*get_final_filename(char default_filename[], int fd);
static void	replace_slashes_by_underscores(char filename[]);
static char	*append_random_char(int fd, char const filename[]);

char	*get_random_filename(char const delim[])
{
	int		fd;
	char	*default_filename;
	char	*final_filename;

	default_filename = get_default_filename(delim);
	if (default_filename == NULL)
		return (NULL);
	fd = open(RANDOM_FILE, O_RDONLY);
	if (fd == -1)
	{
		perror(RANDOM_FILE);
		free(default_filename);
		return (NULL);
	}
	final_filename = get_final_filename(default_filename, fd);
	if (close(fd) == -1)
		perror(RANDOM_FILE);
	return (final_filename);
}

static char	*get_default_filename(char const delim[])
{
	char		*filename;
	char *const	delim_dup = ft_strdup(delim);

	if (delim_dup == NULL)
	{
		perror("get_default_filename():ft_strdup()");
		return (NULL);
	}
	replace_slashes_by_underscores(delim_dup);
	filename = ft_strjoin("/tmp/.heredoc-", delim_dup);
	free(delim_dup);
	if (filename == NULL)
		perror("get_default_filename():ft_strjoin()");
	return (filename);
}

static char	*get_final_filename(char default_filename[], int fd)
{
	char	*final_filename;
	char	*temp;

	final_filename = default_filename;
	while (access(final_filename, F_OK) != -1)
	{
		temp = append_random_char(fd, final_filename);
		free(final_filename);
		if (temp == NULL)
			return (NULL);
		final_filename = temp;
	}
	return (final_filename);
}

static void	replace_slashes_by_underscores(char filename[])
{
	char	*slash;

	slash = ft_strchr(filename, '/');
	while (slash != NULL)
	{
		*slash = '_';
		slash = ft_strchr(slash, '/');
	}
}

static char	*append_random_char(int fd, char const filename[])
{
	char	*new_filename;
	char	append[2];
	ssize_t	bytes;

	append[1] = '\0';
	while (1)
	{
		bytes = read(fd, append, 1);
		if (bytes <= 0)
		{
			perror("append_random_char():read()");
			return (NULL);
		}
		if (ft_isalnum(append[0]))
			break ;
	}
	new_filename = ft_strjoin(filename, append);
	if (new_filename == NULL)
	{
		perror("append_random_char():ft_strjoin()");
		return (NULL);
	}
	return (new_filename);
}
