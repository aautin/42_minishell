/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:03:01 by aautin            #+#    #+#             */
/*   Updated: 2024/04/29 20:47:45 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft/libft.h"

#include "getenv.h"
#include "getenv_utils.h"

#define EXPORT_ERROR_MSG	"export: not a valid identifier\n"

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

static int	is_valid_arg(char *arg, char *ptr)
{
	if (ptr == NULL)
		return (0);
	*ptr = '\0';
	if(!is_validname(arg))
	{
		write(STDERR_FILENO, EXPORT_ERROR_MSG, ft_strlen(EXPORT_ERROR_MSG));
		return (0);
	}
	*ptr = '=';
	return (1);
}

int	builtin_export(char **argv, t_list **envp)
{
	char	*ptr;
	t_list	*current;
	int		exit_status;

	exit_status = 0;
	while (*(++argv))
	{
		ptr = ft_strchr(*argv, '=');
		if (!is_valid_arg(*argv, ptr))
		{
			exit_status = 1;
			continue ;
		}
		*ptr = '\0';
		current = find_env(*envp, *argv);
		if (current == NULL)
			add_env(envp, *argv, ptr + 1);	
		else
			modify_env(current, *argv, ptr + 1);
		*ptr = '=';
	}
	return (exit_status);
}
