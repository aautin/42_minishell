/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/20 10:39:23 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "execution.h"
#include "getenv.h"
#include "handle_signals.h"
#include "heredoc.h"
#include "list_utils.h"
#include "minishell.h"
#include "parser.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*line;
	int			status;
	t_minishell	ms;
	t_list		*bad_node;

	ms.is_interactive = isatty(STDIN_FILENO);
	ms.envl = create_env(envp);
	ms.last_exit_status = EXIT_SUCCESS;
	init_sigint(H_MINISHELL);
	init_sigquit(H_MINISHELL);
	while (1)
	{
		ms.tokens = NULL;
		ms.head_heredoc = NULL;
		line = ask_input("minishell> ", ms.is_interactive);
		if (g_sig != 0)
			ms.last_exit_status = SIG_RETURN + g_sig;
		g_sig = 0;
		if (line == NULL)
			break ;
		if (ms.is_interactive && *line != '\0')
			add_history(line);
		status = tokenize(&ms.tokens, line);
		free(line);
		if (status == 2)
			break ;
		if (!status && ms.tokens != NULL)
		{
			bad_node = verify_tokens(ms.tokens);
			if (bad_node != NULL)
			{
				printf("Unexpected token '%s'\n", ((t_token *)bad_node->content)->data);
				ms.last_exit_status = 2;
			}
			else if (!retrieve_heredoc(&ms))
			{
				ms.current_heredoc = ms.head_heredoc;
				if (bad_node == NULL)
				{
					if (execute_line(&ms))
						break ;
				}
			}
			if (g_sig != 0)
				ms.last_exit_status = SIG_RETURN + g_sig;
			g_sig = 0;
			ft_lstclear(&ms.head_heredoc, &free_heredoc);
		}
		else if (status == 1)
		{
			ft_putstr_fd("Error : quote not closed\n", STDERR_FILENO);
			ms.last_exit_status = 2;
		}
		ft_lstclear(&ms.tokens, &free_token);
		init_sigint(H_MINISHELL);
		printf("EXIT STATUS IS %d\n", ms.last_exit_status);
	}
	ft_lstclear(&ms.tokens, &free_token);
	ft_lstclear(&ms.head_heredoc, &free_heredoc);
	ft_lstclear(&ms.envl, &free);
	if (ms.is_interactive)
		rl_clear_history();
	return (ms.last_exit_status);
}
