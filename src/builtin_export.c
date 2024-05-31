/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:03:01 by aautin            #+#    #+#             */
/*   Updated: 2024/05/31 18:06:42 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "getenv.h"
#include "getenv_utils.h"

#define NOT_VALID_ARG_MSG	": not a valid identifier\n"

static int	is_validname(char const name[])
{
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	name++;
	while (*name != '\0')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

static int	is_valid_arg(char arg[], char *ptr)
{
	char	*msg_error;

	if (!is_validname(arg))
	{
		*ptr = '=';
		msg_error = ft_strjoin(arg, NOT_VALID_ARG_MSG);
		if (msg_error == NULL)
			perror("is_valid_arg():ft_strjoin()");
		else
			write(STDERR_FILENO, msg_error, ft_strlen(msg_error));
		free(msg_error);
		return (0);
	}
	return (1);
}

int	builtin_export(char **argv, t_list **envp)
{
	char	*ptr;
	t_list	*current;
	int		exit_status;

	exit_status = 0;
	while (*(++argv) != NULL)
	{
		ptr = ft_strchr(*argv, '=');
		if (ptr != NULL)
		{
			*ptr = '\0';
			if (is_valid_arg(*argv, ptr))
			{
				current = find_env(*envp, *argv);
				if (current == NULL)
					add_env(envp, *argv, ptr + 1);
				else
					modify_env(current, *argv, ptr + 1);
				continue ;
			}
		}
		exit_status = 1;
	}
	return (exit_status);
}
