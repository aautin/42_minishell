/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:48 by aautin            #+#    #+#             */
/*   Updated: 2024/05/15 16:57:46 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

int	builtin_pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == NULL)
	{
		perror("builtin_pwd():getcwd()");
		return (1);
	}
	if (write(STDOUT_FILENO, buff, ft_strlen(buff)) == -1)
	{
		perror("builtin_pwd():write()");
		return (1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
