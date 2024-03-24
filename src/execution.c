/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:45:04 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/24 18:35:54 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "libft/libft.h"

#include "builtin.h"
#include "exec_cmd.h"
#include "execution_utils.h"
#include "parser.h"
#include "pipeline.h"
#include "redirections.h"
#include "handle_signals.h"
#include "minishell.h"
#include "utils.h"

#define SIG_RETURN 128

static void	execute_simple_cmd(t_minishell *ms, t_simple_cmd *simple_cmd);
static void	create_process(t_minishell *ms, t_simple_cmd *simple_cmd,
				char **argv);
static void	wait_all(t_simple_cmd *simple_cmd);
static int	get_exit_status(int wstatus);

int	execute_line(t_minishell *ms)
{
	t_simple_cmd	simple_cmd;

	ft_bzero(&simple_cmd, sizeof(simple_cmd));
	simple_cmd.first = ms->tokens;
	while (simple_cmd.first != NULL)
	{
		simple_cmd.last = get_control_operator(simple_cmd.first->next);
		simple_cmd.pipeline.mode
			= get_pipe_mode(simple_cmd.first, simple_cmd.last);
		if (simple_cmd.pipeline.mode & P_OUTPUT)
		{
			if (pipe(simple_cmd.pipeline.fd) == -1)
			{
				perror("execute_line():pipe()");
				return (EXIT_FAILURE);
			}
		}
		execute_simple_cmd(ms, &simple_cmd);
		close_pipes(&simple_cmd.pipeline);
		wait_all(&simple_cmd);
		if (simple_cmd.last == NULL || !(((t_token *)simple_cmd.last->content)->type & T_PIPE))
			ms->last_exit_status = simple_cmd.proc.exit_status;
		simple_cmd.first = simple_cmd.last;
	}
	return (simple_cmd.proc.exit_status);
}

static void	execute_simple_cmd(t_minishell *ms, t_simple_cmd *simple_cmd)
{
	t_list		*args;
	char		**argv;

	simple_cmd->proc.pid = -1;
	simple_cmd->proc.exit_status = EXIT_FAILURE;
	args = NULL;
	if (find_args(&args, ms, simple_cmd->first, simple_cmd->last))
		return ;
	argv = listtoken_to_tabstr(args);
	ft_lstclear(&args, NULL);
	if (argv == NULL)
		return ;
	if (!is_a_builtin(argv[0]) || simple_cmd->pipeline.mode != P_NONE)
		create_process(ms, simple_cmd, argv);
	else
		simple_cmd->proc.exit_status = execute_builtin(ms, argv);
	free(argv);
}

static void	create_process(t_minishell *ms, t_simple_cmd *simple_cmd,
		char **argv)
{
	simple_cmd->proc.pid = fork();
	if (simple_cmd->proc.pid == -1)
	{
		perror("create_process():fork()");
		simple_cmd->proc.exit_status = 1;
		return ;
	}
	if (simple_cmd->proc.pid == 0)
	{
		init_signals(1);
		if (!apply_pipe_redirections(&simple_cmd->pipeline)
			&& !apply_normal_redirections(simple_cmd->first, simple_cmd->last))
			simple_cmd->proc.exit_status = prepare_cmd(ms, argv);
		ft_lstclear(&ms->tokens, &free_token);
		ft_lstclear(&ms->envl, &free);
		free(argv);
		exit(simple_cmd->proc.exit_status);
	}
}

static void	wait_all(t_simple_cmd *simple_cmd)
{
	int				wstatus;
	t_token			*token;
	pid_t			proc_waited;
	pid_t			last_pid;
	t_list *const	last = simple_cmd->last;

	if (simple_cmd->proc.pid == -1)
		return ;
	token = NULL;
	if (last != NULL)
		token = last->content;
	if (token != NULL && (token->type & T_PIPE))
		return ;
	proc_waited = waitpid(-1, &wstatus, WUNTRACED);
	while (proc_waited <= 0 && proc_waited != simple_cmd->proc.pid)
		proc_waited = waitpid(-1, &wstatus, WUNTRACED);
	proc_waited = waitpid(-1, NULL, WUNTRACED);
	last_pid = proc_waited;
	while (proc_waited != last_pid)
	{
		last_pid = proc_waited;
		proc_waited = waitpid(-1, NULL, WUNTRACED);
	}
	simple_cmd->proc.exit_status = get_exit_status(wstatus);
}

static int	get_exit_status(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (SIG_RETURN + WTERMSIG(wstatus));
	else if (WIFSTOPPED(wstatus))
		return (SIG_RETURN + WSTOPSIG(wstatus));
	return (0);
}
