/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:48 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 19:57:32 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

#include "libft/libft.h"

#include "minishell.h"
#include "handle_signals.h"

int	g_sig = 0;

static void	sigint_ms_handler(int signum);
static void	sigint_heredoc_handler(int signum);

void	init_sigquit(t_handler_sig mode)
{
	struct sigaction	act;

	if (sigaction(SIGQUIT, NULL, &act) != -1)
	{
		if (mode == H_DEFAULT)
			act.sa_handler = SIG_DFL;
		else if (mode == H_MINISHELL)
			act.sa_handler = SIG_IGN;
		sigemptyset(&act.sa_mask);
		sigaction(SIGQUIT, &act, NULL);
	}
}

void	init_sigint(t_handler_sig mode)
{
	struct sigaction	act;

	if (sigaction(SIGINT, NULL, &act) != -1)
	{
		if (mode == H_DEFAULT)
			act.sa_handler = SIG_DFL;
		else if (mode == H_MINISHELL)
			act.sa_handler = &sigint_ms_handler;
		else if (mode == H_HEREDOC)
			act.sa_handler = &sigint_heredoc_handler;
		else if (mode == H_WAIT)
			act.sa_handler = SIG_IGN;
		sigemptyset(&act.sa_mask);
		sigaction(SIGINT, &act, NULL);
	}
}

static void	sigint_ms_handler(int signum)
{
	g_sig = signum;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_heredoc_handler(int signum)
{
	g_sig = signum;
	close(STDIN_FILENO);
}
