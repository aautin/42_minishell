/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:45:04 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 18:15:28 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "libft/libft.h"

#include "files.h"
#include "parser.h"
#include "pipeline.h"
#include "redirections.h"

#define SIG_RETURN 128

int		add_to_list(t_list **tokens, t_token *token);
int		exec_prog(char **argv, char **envp);
void	free_token(void *content);

typedef struct s_process
{
	pid_t	pid;
	int		exit_status;
}	t_process;

typedef struct s_simple_cmd
{
	t_list		*first;
	t_list		*last;
	t_pipe		pipeline;
	t_process	proc;
}	t_simple_cmd;

static int	find_args(t_list *current, t_list *last, t_list **args)
{
	int		is_redirection;
	t_token	*token;

	is_redirection = 0;
	while (current != last)
	{
		token = current->content;
		if (token->type & T_REDIRECT_OPERATOR)
			is_redirection = 1;
		else if (token->type & T_WORD)
		{
			if (!is_redirection && add_to_list(args, token))
			{
				ft_lstclear(args, NULL);
				return (1);
			}
			is_redirection = 0;
		}
		current = current->next;
	}
	return (0);
}

static t_list	*get_control_operator(t_list *current)
{
	t_token	*token;

	while (current != NULL)
	{
		token = current->content;
		if (token->type & T_CONTROL_OPERATOR)
			break ;
		current = current->next;
	}
	return (current);
}

static	char	**list_to_tabstr(t_list	*current)
{
	int		size;
	char	**tab;
	int		i;
	t_token	*token;

	size = ft_lstsize(current);
	tab = malloc((size + 1) * sizeof(char *));
	if (tab == NULL)
	{
		perror("list_to_tabstr():malloc()");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		token = current->content;
		parse_token(token);
		tab[i] = token->data;
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	is_a_builtin(char cmd[])
{
	char const *const	builtin_names[] = {"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL};
	int					i;
	size_t				len;

	if (cmd == NULL || *cmd == '\0')
		return (0);
	len = ft_strlen(cmd);
	i = 0;
	while (builtin_names[i] != NULL)
	{
		if (ft_strncmp(cmd, builtin_names[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	create_process(t_list *tokens, t_simple_cmd *simple_cmd,
		char **argv, char **envp)
{
	int			exit_status;

	simple_cmd->proc.pid = fork();
	if (simple_cmd->proc.pid == -1)
	{
		perror("create_process():fork()");
		simple_cmd->proc.exit_status = 1;
		return ;
	}
	if (simple_cmd->proc.pid == 0)
	{
		exit_status = EXIT_FAILURE;
		if (!apply_pipe_redirections(&simple_cmd->pipeline)
			&& !apply_normal_redirections(simple_cmd->first, simple_cmd->last))
			exit_status = exec_prog(argv, envp);
		ft_lstclear(&tokens, &free_token);
		free(argv);
		exit(exit_status);
	}
	simple_cmd->proc.exit_status = 0;
}

static void	execute_simple_cmd(t_list *tokens, t_simple_cmd *simple_cmd, char **envp)
{
	t_list		*args;
	char		**argv;

	simple_cmd->proc.pid = -1;
	simple_cmd->proc.exit_status = 0;
	args = NULL;
	if (find_args(simple_cmd->first, simple_cmd->last, &args))
		return ;
	argv = list_to_tabstr(args);
	ft_lstclear(&args, NULL);
	if (argv == NULL)
		return ;
	if (!is_a_builtin(argv[0]) || simple_cmd->pipeline.mode != P_NONE)
		create_process(tokens, simple_cmd, argv, envp);
	free(argv);
}

void	wait_all(t_simple_cmd *simple_cmd)
{
	t_list *const	last = simple_cmd->last;
	t_token			*token;
	pid_t			proc_waited;

	if (simple_cmd->proc.pid == -1)
		return ;
	token = NULL;
	if (last != NULL)
		token = last->content;
	if (token == NULL || !(token->type & T_PIPE))
	{
		proc_waited = waitpid(-1, &simple_cmd->proc.exit_status, WUNTRACED);
		while (proc_waited != simple_cmd->proc.pid && errno != ECHILD)
			proc_waited = waitpid(-1, &simple_cmd->proc.exit_status, WUNTRACED);
		while (errno != ECHILD)
			wait(NULL);
		if (WIFEXITED(simple_cmd->proc.exit_status))
			simple_cmd->proc.exit_status = WEXITSTATUS(simple_cmd->proc.exit_status);
		else if (WIFSIGNALED(simple_cmd->proc.exit_status))
			simple_cmd->proc.exit_status = SIG_RETURN + WTERMSIG(simple_cmd->proc.exit_status);
	}
}

int	execute_line(t_list *tokens, char **envp)
{
	t_simple_cmd	simple_cmd;

	ft_bzero(&simple_cmd, sizeof(simple_cmd));
	simple_cmd.first = tokens;
	while (simple_cmd.first != NULL)
	{
		simple_cmd.last = get_control_operator(simple_cmd.first->next);
		simple_cmd.pipeline.mode = get_pipe_mode(simple_cmd.first, simple_cmd.last);
		if (simple_cmd.pipeline.mode & P_OUTPUT)
		{
			if (pipe(simple_cmd.pipeline.fd) == -1)
			{
				perror("execute_line():pipe()");
				return (EXIT_FAILURE);
			}
		}
		execute_simple_cmd(tokens, &simple_cmd, envp);
		close_pipes(&simple_cmd.pipeline);
		wait_all(&simple_cmd);
		printf("EXIT STATUS : %d\n", simple_cmd.proc.exit_status);
		simple_cmd.first = simple_cmd.last;
	}
	return (0);
}
