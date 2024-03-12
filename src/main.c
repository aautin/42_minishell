/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/12 16:49:32 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

int	parse_data_len(char *data, int data_len);

int	main(int argc, char **argv)
{
	(void) argc;
	parse_data_len(argv[1], ft_strlen(argv[1]));
	// char	*line;
	// t_list	*tokens;

	// tokens = NULL;
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (line == NULL)
	// 		break ;
	// 	if (*line != '\0')
	// 		add_history(line);
	// 	ft_putstr_fd(line, STDOUT_FILENO);
	// 	free(line);
	// }
	// rl_clear_history();
	return (EXIT_SUCCESS);
}
