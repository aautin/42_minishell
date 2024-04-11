/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:48 by aautin            #+#    #+#             */
/*   Updated: 2024/04/11 15:26:44 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_pwd.h"

int	builtin_pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == NULL)
	{
		perror("builtin_pwd():getcwd()");
		return (1);
	}
	if (printf("%s\n", buff) == -1)
	{
		perror("builtin_pwd():printf()");
		return (1);
	}
	return (0);
}
