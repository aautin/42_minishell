/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 18:22:20 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "execution.h"
#include "parser.h"
#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	int		status;
	t_list	*tokens;

	while (1)
	{
		tokens = NULL;
		line = ask_input("minishell> ");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		status = tokenize(&tokens, line);
		free(line);
		if (!status && tokens != NULL)
		{
			bad_node = verify_tokens(tokens);
			if (bad_node != NULL)
				printf("Unexpected token '%s'\n", ((t_token *)bad_node->content)->data);
			execute_line(tokens, envp);
		}
		else if (status == 1)
			ft_putstr_fd("Error : quote not closed\n", STDERR_FILENO);
		ft_lstclear(&tokens, &free_token);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
