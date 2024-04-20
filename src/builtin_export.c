/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:03:01 by aautin            #+#    #+#             */
/*   Updated: 2024/04/20 20:21:29 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

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
		write(1, EXPORT_ERROR_MSG, ft_strlen(EXPORT_ERROR_MSG));
		return (0);
	}
	*ptr = '=';
	return (1);
}

static t_list	*find_env(char *arg, int arg_size, t_list *current)
{
	while (current)
	{
		if (ft_strncmp(*arg, current->content, arg_size) == 0)
			break ;
		current = current->next;
	}
	return (current);
}

int	builtin_export(char **argv, t_list **envp)
{
	char	*ptr;
	t_list	*current;
	int		arg_size;
	int		exit_status;

	exit_status = 0;
	while (*(++argv))
	{
		arg_size = ft_strlen(*argv) + 1;
		ptr = ft_strchr(*argv, '=');
		if (is_valid_arg(*argv, ptr) == 0)
		{
			exit_status = 1;
			continue ;
		}
		current = find_env(*argv, arg_size, *envp);
		*ptr = '\0';
		if (current == NULL)
			add_env(envp, *argv, ptr + 1);	
		else
			modify_env(current, *argv, ptr + 1);
		*ptr = '=';
	}
	return (exit_status);
}
