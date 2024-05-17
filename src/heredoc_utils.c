/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:07:11 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/17 18:58:48 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#define RANDOM_FILE	"/dev/random"

static void	replace_slashes_by_underscores(char filename[]);
static char	*append_random_char(int fd, char const filename[]);

char	*get_random_filename(char const delim[])
{
	char		*filename;
	char		*temp;
	int const	fd = open(RANDOM_FILE, O_RDONLY);
	char *const	delim_dup = ft_strdup(delim);

	if (fd == -1 || delim_dup == NULL)
	{
		perror("get_random_filename()");
		free(delim_dup);
		close(fd);
		return (NULL);
	}
	replace_slashes_by_underscores(delim_dup);
	filename = ft_strjoin("/tmp/.temp-", delim_dup);
	free(delim_dup);
	if (filename == NULL)
	{
		perror("get_random_filename()");
		close(fd);
		return (NULL);
	}
	while (access(filename, F_OK) != -1)
	{
		temp = append_random_char(fd, filename);
		free(filename);
		if (temp == NULL)
		{
			perror("get_random_filename()");
			close(fd);
			return (NULL);
		}
		filename = temp;
	}
	if (close(fd) == -1)
		perror(RANDOM_FILE);
	return (filename);
}

static void	replace_slashes_by_underscores(char filename[])
{
	char	*slash;

	slash = ft_strchr(filename, '/');
	while (slash != NULL)
	{
		*slash = '_';
		slash = ft_strchr(filename, '/');
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
