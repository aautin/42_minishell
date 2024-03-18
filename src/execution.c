/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:45:04 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 21:06:48 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "files.h"
#include "parser.h"
#include "redirections.h"

int		add_to_list(t_list **tokens, t_token *token);
int		exec_prog(char **argv, char **envp);
void	free_token(void *content);

void	dummy(void *content)
{
	(void)content;
}

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

static t_list	*find_args(t_list *current, t_list *last)
{
	int		is_redirection;
	t_token	*token;
	t_list	*argv;

	is_redirection = 0;
	argv = NULL;
	while (current != last)
	{
		token = current->content;
		if (token->type & T_REDIRECT_OPERATOR)
			is_redirection = 1;
		else if (token->type & T_WORD)
		{
			if (!is_redirection && !add_to_list(&argv, token))
			{
				ft_lstclear(&argv, &dummy);
				return (NULL);
			}
			is_redirection = 0;
		}
		current = current->next;
	}
	return (argv);
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
		apply_pipe_redirections(&simple_cmd->pipeline);
		apply_redirections(simple_cmd->first, simple_cmd->last);
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
	args = find_args(simple_cmd->first, simple_cmd->last);
	if (args == NULL)
		return ;
	argv = list_to_tabstr(args);
	ft_lstclear(&args, &dummy);
	if (argv == NULL)
		return ;
	if (!is_a_builtin(argv[0]) || simple_cmd->pipeline.mode != P_NONE)
		create_process(tokens, simple_cmd, argv, envp);
	free(argv);
}

static void	close_pipes(t_pipe *pipeline)
{
	if (pipeline->mode & P_INPUT)
	{
		if (close(pipeline->prev_fd_in) == -1)
			perror("close_pipes():close()");
	}
	if (pipeline->mode & P_OUTPUT)
	{
		if (close(pipeline->fd[1]) == -1)
			perror("close_pipes():close()");
		pipeline->prev_fd_in = pipeline->fd[0];
	}
}

int	execute_line(t_list *tokens, char **envp)
{
	t_simple_cmd	simple_cmd;

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
		simple_cmd.first = simple_cmd.last;
	}
	return (0);
}
