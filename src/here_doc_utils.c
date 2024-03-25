/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:07:11 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 16:20:50 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

static void	replace_slashes_by_underscores(char filename[]);
static char	*append_random_char(int fd, char const filename[]);

char	*get_random_filename(char const delim[])
{
	char		*filename;
	char		*temp;
	int const	fd = open("/dev/random", O_RDONLY);

	if (fd == -1)
	{
		perror("/dev/random");
		return (NULL);
	}
	filename = ft_strjoin(".", delim);
	replace_slashes_by_underscores(filename);
	while (access(filename, F_OK) != -1)
	{
		temp = append_random_char(fd, filename);
		free(filename);
		if (temp == NULL)
			return (NULL);
		filename = temp;
	}
	if (close(fd) == -1)
		perror("/dev/random");
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
