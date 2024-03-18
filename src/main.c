/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 18:39:26 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "getenv.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_list *new_envp = create_env(envp);

	if (new_envp == NULL)
		return (EXIT_FAILURE);

	t_list *node = new_envp;
	while (node)
	{
		printf("%s\n", (char *) node->content);
		node = node->next;
	}
	printf("\nFT_GETENV:\n");
	printf("$HOME = %s\n", ft_getenv(new_envp, "HOME"));
	printf("$NOTHING = %s\n", ft_getenv(new_envp, "NOTHING"));
	printf("$USER = %s\n", ft_getenv(new_envp, "USER"));
	printf("$TERM = %s\n", ft_getenv(new_envp, "TERM"));
	printf("$_ = %s\n", ft_getenv(new_envp, "_"));
	printf("$SYSTEMD_EXEC_PID = %s\n", ft_getenv(new_envp, "SYSTEMD_EXEC_PID"));
	printf("$SYSTEMD_EXEC_PID = %s\n", ft_getenv(new_envp, "SYSTEMD_EXEC_PID"));
	ft_lstclear(&new_envp, &free);
	return (EXIT_SUCCESS);
}
