/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/28 17:56:07 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "execution.h"
#include "getenv.h"
#include "handle_signals.h"
#include "here_doc.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*line;
	int			status;
	t_minishell	ms;

	ms.envl = create_env(envp);
	init_signals(0);
	while (1)
	{
		ms.last_exit_status = 0;
		ms.tokens = NULL;
		ms.head_here_doc = NULL;
		line = ask_input("minishell> ");
		if (g_sig != 0)
			ms.last_exit_status = 128 + g_sig;
		g_sig = 0;
		if (line == NULL)
			break ;
		if (isatty(STDIN_FILENO) && *line != '\0')
			add_history(line);
		status = tokenize(&ms.tokens, line);
		free(line);
		if (status == 2)
			break ;
		if (!status && ms.tokens != NULL)
		{
			bad_node = verify_tokens(ms.tokens);
			if (bad_node != NULL)
				printf("Unexpected token '%s'\n", ((t_token *)bad_node->content)->data);
			if (!retrieve_heredoc(&ms))
			{
				ms.current_here_doc = ms.head_here_doc;
				if (bad_node == NULL && execute_line(&ms))
					break ;
				ft_lstclear(&ms.head_here_doc, &free_here_doc);
			}
			if (g_sig != 0)
				ms.last_exit_status = 128 + g_sig;
			g_sig = 0;
		}
		else if (status == 1)
			ft_putstr_fd("Error : quote not closed\n", STDERR_FILENO);
		ft_lstclear(&ms.tokens, &free_token);
		printf("EXIT STATUS IS %d\n", ms.last_exit_status);
	}
	ft_lstclear(&ms.tokens, &free_token);
	ft_lstclear(&ms.envl, &free);
	rl_clear_history();
	return (ms.last_exit_status);
}
