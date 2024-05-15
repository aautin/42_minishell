/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:20:31 by aautin            #+#    #+#             */
/*   Updated: 2024/05/15 16:42:30 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#define NORMAL_MODE 0
#define NO_NEWLINE_MODE 1

static int	get_status(char const arg[])
{
	if (*arg != '-')
		return (NORMAL_MODE);
	arg++;
	if (*arg == '\0')
		return (NORMAL_MODE);
	while (*arg == 'n')
		arg++;
	if (*arg == '\0')
		return (NO_NEWLINE_MODE);
	return (NORMAL_MODE);
}

static char	*join_string_argv(char **argv, char format)
{
	char	*output;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (argv[i] != NULL)
		len += ft_strlen(argv[i++]);
	len = len + i + (format == NORMAL_MODE);
	output = malloc(len * sizeof(char));
	if (output == NULL)
		return (perror("join_string_argv():malloc()"), NULL);
	output[0] = '\0';
	i = 0;
	while (argv[i])
	{
		ft_strlcat(output, argv[i++], len);
		if (argv[i])
			ft_strlcat(output, " ", len);
	}
	if (format == NORMAL_MODE)
		ft_strlcat(output, "\n", len);
	return (output);
}

int	builtin_echo(char **argv)
{
	char	format;
	char	*output;

	if (*(argv + 1) == NULL)
	{
		if (write(1, "\n", 1) == -1)
			return (perror("echo():write()"), 1);
		return (0);
	}
	format = NORMAL_MODE;
	while (*(++argv))
	{
		if (get_status(*argv) != NO_NEWLINE_MODE)
			break ;
		else
			format = NO_NEWLINE_MODE;
	}
	if (*argv == NULL && format == NO_NEWLINE_MODE)
		return (0);
	output = join_string_argv(argv, format);
	if (output == NULL)
		return (1);
	if (write(1, output, ft_strlen(output)) == -1)
		return (perror("echo():write()"), free(output), 1);
	return (free(output), 0);
}
