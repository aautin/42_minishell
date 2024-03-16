/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:20:31 by aautin            #+#    #+#             */
/*   Updated: 2024/03/16 15:02:52 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#define	SIMPLE_STRING 0
#define	NEWLINE_OPTION 1
#define	ANOTHER_OPTION 2

static int	get_status(char *arg)
{
	if (*arg != '-')
		return (SIMPLE_STRING);
	while ('n' == *(arg + 1))
		arg++;
	if ((ft_isspace(*(arg + 1)) || !*(arg + 1)) && *arg != '-')
		return (NEWLINE_OPTION);
	return (SIMPLE_STRING);
}

static char	*join_string_argv(char **argv, char format)
{
	char			*output;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = 0;
	while (argv[i])
		len += ft_strlen(argv[i++]);
	output = malloc((len + i + (format != NEWLINE_OPTION)) * sizeof(char));
	printf("[echo] output's size: %d\n", len + i + (format != NEWLINE_OPTION));
	if (output == NULL)
		return (NULL);
	len = 0;
	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
			output[len++] = (*argv)[i++];
		if (*(argv + 1))
			output[len++] = ' ';
		argv++;
	}
	if (format != NEWLINE_OPTION)
		output[len++] = '\n';
	return (output[len] = '\0', output);
}

int	builtin_echo(char **argv)
{
	char	format;
	char	*output;

	format = SIMPLE_STRING;
	while (*argv)
	{
		if (get_status(*argv) != NEWLINE_OPTION)
			break ;
		else
			format = NEWLINE_OPTION;
		argv++;
	}
	output = join_string_argv(argv, format);
	if (output == NULL)
		return (1);
	printf("%s", output);
	free(output);
	return (0);
}
