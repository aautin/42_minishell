/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/11 20:29:54 by aautin           ###   ########.fr       */
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
#include "redirections.h"

static void	init_minishell(t_minishell *ms, char **envp);
static void	deinit_minishell(t_minishell *ms);
static int	retrieve_tokens_line(t_minishell *ms);
static int	use_tokens(t_minishell *ms);

int	main(int argc, char **argv, char **envp)
{
	int			status;
	t_minishell	ms;

	(void)argc;
	(void)argv;
	init_minishell(&ms, envp);
	while (1)
	{
		ms.tokens = NULL;
		ms.head_heredoc = NULL;
		status = retrieve_tokens_line(&ms);
		if (status == 2)
			break ;
		if (!status && ms.tokens != NULL)
		{
			if (use_tokens(&ms))
				break ;
		}
		ft_lstclear(&ms.tokens, &free_token);
		init_sigint(H_MINISHELL);
	}
	deinit_minishell(&ms);
	return (ms.last_exit_status);
}

static void	init_minishell(t_minishell *ms, char **envp)
{
	ms->is_interactive = isatty(STDIN_FILENO);
	ms->envl = create_env(envp);
	ms->last_exit_status = EXIT_SUCCESS;
	init_sigint(H_MINISHELL);
	init_sigquit(H_MINISHELL);
}

static void	deinit_minishell(t_minishell *ms)
{
	ft_lstclear(&ms->tokens, &free_token);
	ft_lstclear(&ms->head_heredoc, &free_heredoc);
	ft_lstclear(&ms->envl, &free);
	if (ms->is_interactive)
	{
		rl_clear_history();
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	}
}

static int	retrieve_tokens_line(t_minishell *ms)
{
	int			status;
	char *const	line = ask_input("minishell> ", ms->is_interactive);

	if (g_sig != 0)
		ms->last_exit_status = SIG_RETURN + g_sig;
	g_sig = 0;
	if (line == NULL)
		return (2);
	if (ms->is_interactive && *line != '\0')
		add_history(line);
	status = tokenize(&ms->tokens, line);
	free(line);
	if (status == 1)
	{
		ft_putstr_fd("Error : quote not closed\n", STDERR_FILENO);
		ms->last_exit_status = 2;
	}
	return (status);
}

static int	use_tokens(t_minishell *ms)
{
	int				std_fd[3];
	t_list *const	bad = verify_tokens(ms->tokens);

	if (bad != NULL)
	{
		ms->last_exit_status = 2;
		if (!save_std_fd(std_fd))
		{
			redirect_fd(STDERR_FILENO, STDOUT_FILENO);
			printf("Unexpected token '%s'\n", ((t_token *)bad->content)->data);
			reset_std_fd(std_fd);
		}
		return (0);
	}
	if (!retrieve_heredoc(ms))
	{
		ms->current_heredoc = ms->head_heredoc;
		if (execute_line(ms))
			return (1);
	}
	if (g_sig != 0)
		ms->last_exit_status = SIG_RETURN + g_sig;
	g_sig = 0;
	ft_lstclear(&ms->head_heredoc, &free_heredoc);
	return (0);
}
