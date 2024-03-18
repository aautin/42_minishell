/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:20:31 by aautin            #+#    #+#             */
/*   Updated: 2024/03/18 15:38:21 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#define NORMAL_MODE 0
#define NO_NEWLINE_MODE 1

static int	get_status(char *arg)
{
	if (*arg != '-')
		return (NORMAL_MODE);
	arg++;
	if (*arg == '\0')
		return (NORMAL_MODE);
	while ('n' == *arg)
		arg++;
	if (*arg == '\0')
		return (NO_NEWLINE_MODE);
	return (NORMAL_MODE);
}

static char	*join_string_argv(char **argv, char format)
{
	char	*output;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (argv[i])
		len += ft_strlen(argv[i++]);
	len = len + i + (format == NORMAL_MODE);
	output = malloc(len * sizeof(char));
	if (output == NULL)
		return (NULL);
	output[0] = '\0';
	while (*argv)
	{
		ft_strlcat(output, *(argv++), len);
		if (*argv)
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

	format = NORMAL_MODE;
	while (*argv)
	{
		if (get_status(*argv) != NO_NEWLINE_MODE)
			break ;
		else
			format = NO_NEWLINE_MODE;
		argv++;
	}
	output = join_string_argv(argv, format);
	if (output == NULL)
		return (1);
	ft_putstr_fd(output, 1);
	free(output);
	return (0);
}
