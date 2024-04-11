/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:56:05 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 19:33:08 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/wait.h>

#include "libft/libft.h"

#include "execution_utils.h"
#include "handle_signals.h"
#include "parser.h"
#include "print_signals.h"

#define SIG_RETURN	128

static int	get_exit_status(int wstatus);

void	wait_all(t_cmd *cmd)
{
	int				wstatus;
	t_token			*token;
	pid_t			proc_waited;
	pid_t			last_pid;
	t_list *const	last_token = cmd->last_token;

	if (cmd->proc.pid == -1)
		return ;
	token = NULL;
	if (last_token != NULL)
		token = last_token->content;
	if (token != NULL && (token->type & T_PIPE))
		return ;
	init_sigint(H_WAIT);
	proc_waited = waitpid(-1, &wstatus, WUNTRACED);
	while (proc_waited >= 0 && proc_waited != cmd->proc.pid)
		proc_waited = waitpid(-1, &wstatus, WUNTRACED);
	proc_waited = waitpid(-1, NULL, WUNTRACED);
	last_pid = -1;
	while (proc_waited != last_pid)
	{
		last_pid = proc_waited;
		proc_waited = waitpid(-1, NULL, WUNTRACED);
	}
	cmd->proc.exit_status = get_exit_status(wstatus);
}

static int	get_exit_status(int wstatus)
{
	int	status;

	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSTOPPED(wstatus))
		return (SIG_RETURN + WSTOPSIG(wstatus));
	else if (WIFSIGNALED(wstatus))
	{
		status = WTERMSIG(wstatus);
		print_signal_msg(status);
		return (SIG_RETURN + status);
	}
	return (0);
}
