/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:35:17 by aautin            #+#    #+#             */
/*   Updated: 2024/04/28 18:51:48 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

static char *match_cd_paths(char *cd_paths, )
{
	
	return (NULL);
}

int	builtin_cd(char **argv, t_list **envp) {
	char	*env_val;
	char	*dir_operand;

	if (argv[1] == NULL)
	{
		env_val = ft_getenv(*envp, "HOME");
		if (env_val == NULL || env_val[0] == '\0')
			return (0);
		dir_operand = env_val;
	}
	else if (argv[1][0] == '/')
		dir_operand = argv[1];
	else
	{
		env_val = ft_getenv(*envp, "CDPATH");
		if (env_val != NULL)
		{
			dir_operand = 
		}
	}
	return (0);
}
