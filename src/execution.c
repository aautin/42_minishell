/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:45:04 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/21 16:33:44 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "builtin.h"
#include "exec_cmd.h"
#include "execution_utils.h"
#include "handle_signals.h"
#include "list_utils.h"
#include "minishell.h"
#include "parser.h"
#include "pipeline.h"
#include "redirections.h"
#include "wait_cmds.h"

#define NOT_CHILD	0

static int	simple_cmd(t_minishell *ms, t_cmd *cmd);
static int	prepare_simple_cmd(t_minishell *ms, t_cmd *cmd);
static int	execute_simple_cmd(t_minishell *ms, t_cmd *cmd, char **argv);
static int	create_process(t_minishell *ms, t_cmd *cmd, char **argv);

int	execute_line(t_minishell *ms)
{
	t_cmd	cmd;

	ft_bzero(&cmd, sizeof(cmd));
	cmd.first_token = ms->tokens;
	while (cmd.first_token != NULL)
	{
		cmd.last_token = get_control_operator(cmd.first_token->next);
		if (simple_cmd(ms, &cmd))
			return (1);
		wait_all(&cmd);
		if (cmd.last_token == NULL
			|| !(((t_token *)cmd.last_token->content)->type & T_PIPE))
			ms->last_exit_status = cmd.proc.exit_status;
		cmd.first_token = cmd.last_token;
	}
	return (0);
}

static int	simple_cmd(t_minishell *ms, t_cmd *cmd)
{
	int		status;

	cmd->pipeline.mode = get_pipe_mode(cmd->first_token, cmd->last_token);
	if (cmd->pipeline.mode & P_OUTPUT)
	{
		if (pipe(cmd->pipeline.fd) == -1)
		{
			perror("simple_cmd():pipe()");
			return (1);
		}
	}
	status = prepare_simple_cmd(ms, cmd);
	if (close_pipes(&cmd->pipeline) || status)
		return (1);
	goto_next_heredoc(ms, cmd->first_token, cmd->last_token);
	return (0);
}

static int	prepare_simple_cmd(t_minishell *ms, t_cmd *cmd)
{
	t_list		*args;
	char		**argv;
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
	status = execute_simple_cmd(ms, cmd, argv);
	free(argv);
	return (status);
}

static int	execute_simple_cmd(t_minishell *ms, t_cmd *cmd, char **argv)
{
	int			std_fd[3];

	if (!is_a_builtin(argv[0]) || cmd->pipeline.mode != P_NONE)
		return (create_process(ms, cmd, argv));
	if (!save_std_fd(std_fd))
	{
		init_sigint(H_DEFAULT);
		init_sigquit(H_DEFAULT);
		if (!redirect_files(ms, cmd->first_token, cmd->last_token))
			cmd->proc.exit_status = execute_builtin(ms, argv,
					NOT_CHILD, std_fd);
		init_sigint(H_MINISHELL);
		init_sigquit(H_MINISHELL);
		return (reset_std_fd(std_fd));
	}
	return (0);
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
		init_sigint(H_DEFAULT);
		init_sigquit(H_DEFAULT);
		if (!redirect_pipes(&cmd->pipeline)
			&& !redirect_files(ms, cmd->first_token, cmd->last_token))
			cmd->proc.exit_status = prepare_cmd(ms, argv);
		ft_lstclear(&ms->tokens, &free_token);
		ft_lstclear(&ms->envl, &free);
		ft_lstclear(&ms->head_heredoc, &free);
		free(argv);
		if (ms->is_interactive)
			rl_clear_history();
		exit(cmd->proc.exit_status);
	}
	return (0);
}
