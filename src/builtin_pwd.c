/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:48 by aautin            #+#    #+#             */
/*   Updated: 2024/04/19 18:40:47 by aautin           ###   ########.fr       */
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
		perror("pwd():getcwd()");
		return (1);
	}
	if (write(1, buff, ft_strlen(buff)) == -1)
	{
		perror("pwd():write()");
		return (1);
	}
	write(1, "\n", 1);
	return (0);
}
