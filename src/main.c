/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 19:23:37 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "utils.h"

int	execute_line(t_list *tokens, char **envp);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*line;

	while (1)
	{
		line = ask_input("minishell> ");
		if (line == NULL)
			break ;
		*ft_strrchr(line, '\n') = '\0';
		if (*line != '\0')
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
