/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:48 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/28 16:59:46 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

#include "libft/libft.h"

#include "minishell.h"

int	g_sig = 0;

static void	sigint_handler(int signum);
static void	sigint_heredoc_handler(int signum);

void	init_signals(int is_child)
{
	struct sigaction	act;

	if (sigaction(SIGINT, NULL, &act) != -1)
	{
		if (act.sa_handler != SIG_IGN || is_child)
		{
			act.sa_handler = &sigint_handler;
			if (is_child)
				act.sa_handler = SIG_DFL;
			sigemptyset(&act.sa_mask);
			sigaction(SIGINT, &act, NULL);
		}
	}
	if (sigaction(SIGQUIT, NULL, &act) != -1)
	{
		if (act.sa_handler != SIG_IGN || is_child)
		{
			act.sa_handler = SIG_IGN;
			if (is_child)
				act.sa_handler = SIG_DFL;
			sigemptyset(&act.sa_mask);
			sigaction(SIGQUIT, &act, NULL);
		}
	}
}

void	init_signal_heredoc(void)
{
	struct sigaction	act;

	if (sigaction(SIGINT, NULL, &act) != -1)
	{
		if (act.sa_handler != SIG_IGN)
		{
			act.sa_handler = &sigint_heredoc_handler;
			sigemptyset(&act.sa_mask);
			sigaction(SIGINT, &act, NULL);
		}
	}
}

static void	sigint_heredoc_handler(int signum)
{
	g_sig = signum;
	close(STDIN_FILENO);
}

static void	sigint_handler(int signum)
{
	g_sig = signum;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
