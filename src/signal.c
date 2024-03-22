/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:48 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/22 18:41:17 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	init_signals(int is_child)
{
	struct sigaction	act;

	if (sigaction(SIGINT, NULL, &act) != -1)
	{
		if (act.sa_handler != SIG_IGN)
		{
			act.sa_handler = &sigint_handler;
			if (is_child)
				act.sa_handler = SIG_FDL;
			sigemptyset(act.sa_mask);
			sigaction(SIGINT, &act, NULL);
		}
	}
	if (sigaction(SIGQUIT, NULL, &act) != -1)
	{
		if (act.sa_handler != SIG_IGN)
		{
			act.sa_handler = SIG_IGN;
			if (is_child)
				act.sa_handler = SIG_FDL;
			sigemptyset(act.sa_mask);
			sigaction(SIGQUIT, &act, NULL);
		}
	}
}

static void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
