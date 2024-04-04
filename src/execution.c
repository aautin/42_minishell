/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:45:04 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 18:50:54 by pnguyen-         ###   ########.fr       */
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
#include "handle_signals.h"
#include "minishell.h"
#include "parser.h"
#include "pipeline.h"
#include "print_signals.h"
#include "redirections.h"
#include "utils.h"

#define SIG_RETURN 128

static int	execute_cmd(t_minishell *ms, t_cmd *cmd);
static int	create_process(t_minishell *ms, t_cmd *cmd, char **argv);
static void	wait_all(t_cmd *cmd);
static int	get_exit_status(int wstatus);

int	execute_line(t_minishell *ms)
{
	t_cmd	cmd;
	int		status;

	ft_bzero(&cmd, sizeof(cmd));
	cmd.first_token = ms->tokens;
	while (cmd.first_token != NULL)
	{
		cmd.last_token = get_control_operator(cmd.first_token->next);
		cmd.pipeline.mode = get_pipe_mode(cmd.first_token, cmd.last_token);
		if (cmd.pipeline.mode & P_OUTPUT)
		{
			if (pipe(cmd.pipeline.fd) == -1)
			{
				perror("execute_line():pipe()");
				return (EXIT_FAILURE);
			}
		}
		status = execute_cmd(ms, &cmd);
		close_pipes(&cmd.pipeline);
		if (status)
			return (1);
		goto_next_heredoc(ms, cmd.first_token, cmd.last_token);
		wait_all(&cmd);
		if (cmd.last_token == NULL
				|| !(((t_token *)cmd.last_token->content)->type & T_PIPE))
			ms->last_exit_status = cmd.proc.exit_status;
		cmd.first_token = cmd.last_token;
	}
	return (0);
}

static int	execute_cmd(t_minishell *ms, t_cmd *cmd)
{
	t_list		*args;
	char		**argv;
	int			std_fd[3];
	int			status;

	args = NULL;
	if (find_args(&args, ms, cmd->first_token, cmd->last_token))
		return (1);
	argv = listtoken_to_tabstr(args);
	ft_lstclear(&args, NULL);
	if (argv == NULL)
		return (1);
	cmd->proc.pid = -1;
	cmd->proc.exit_status = EXIT_FAILURE;
	status = 0;
	if (!is_a_builtin(argv[0]) || cmd->pipeline.mode != P_NONE)
		status = create_process(ms, cmd, argv);
	else
	{
		if (!save_std_fd(std_fd))
		{
			if (!redirect_files(cmd->first_token, cmd->last_token,
					&ms->current_heredoc, ms->last_exit_status))
				cmd->proc.exit_status = execute_builtin(ms, argv);
			status = reset_std_fd(std_fd);
		}
	}
	free(argv);
	return (status);
}

static int	create_process(t_minishell *ms, t_cmd *cmd, char **argv)
{
	cmd->proc.pid = fork();
	if (cmd->proc.pid == -1)
	{
		perror("create_process():fork()");
		cmd->proc.exit_status = 1;
		return (1);
	}
	if (cmd->proc.pid == 0)
	{
		init_signals(1);
		if (!redirect_pipes(&cmd->pipeline)
			&& !redirect_files(cmd->first_token, cmd->last_token,
				&ms->current_heredoc, ms->last_exit_status))
			cmd->proc.exit_status = prepare_cmd(ms, argv);
		ft_lstclear(&ms->tokens, &free_token);
		ft_lstclear(&ms->envl, &free);
		ft_lstclear(&ms->head_heredoc, &free);
		free(argv);
		exit(cmd->proc.exit_status);
	}
	return (0);
}

static void	wait_all(t_cmd *cmd)
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
