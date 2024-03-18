/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:45:04 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 19:31:37 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"

int	parse_token(t_token *token);

int	add_to_list(t_list **tokens, t_token *token);

void	dummy(void *content)
{
	(void)content;
}

static t_list	*find_args(t_list *tokens, t_list *last)
{
	int		is_redirection;
	t_token	*token;
	t_list	*argv;

	is_redirection = 0;
	argv = NULL;
	while (tokens != last)
	{
		token = tokens->content;
		if (token->type & T_REDIRECT_OPERATOR)
			is_redirection = 1;
		else if (token->type & T_WORD)
		{
			if (!is_redirection)
			{
				if (!add_to_list(&argv, token))
					return (NULL);
			}
			is_redirection = 0;
		}
		tokens = tokens->next;
	}
	return (argv);
}

static t_list	*get_control_operator(t_list *tokens)
{
	t_token	*token;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type & T_CONTROL_OPERATOR)
			break ;
		tokens = tokens->next;
	}
	return (tokens);
}

static	char	**list_to_tabstr(t_list	*tokens)
{
	int		size;
	char	**tab;
	int		i;
	t_token	*token;

	size = ft_lstsize(tokens);
	tab = malloc((size + 1) * sizeof(char *));
	if (tab == NULL)
	{
		perror("list_to_tabstr():malloc()");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		token = tokens->content;
		parse_token(token);
		tab[i] = token->data;
		tokens = tokens->next;
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
	int				i;
	size_t const	len = ft_strlen(cmd);

	if (cmd == NULL)
		return (0);
	i = 0;
	while (builtin_names[i] != NULL)
	{
		if (ft_strncmp(cmd, builtin_names[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

typedef enum e_pipe_mode
{
	P_NONE = 0u,
	P_INPUT = (1u << 0),
	P_OUTPUT = (1u << 1)
}	t_pipe_mode;

typedef struct s_pipe
{
	int			fd[2];
	int			prev_fd_in;
	t_pipe_mode	mode;
}	t_pipe;

static t_pipe_mode	get_pipe_mode(t_list *current, t_list *last_control_operator)
{
	t_token		*token;
	t_pipe_mode	mode;

	mode = P_NONE;
	token = current->content;
	if (token->type & T_PIPE)
		mode |= P_INPUT;
	if (last_control_operator == NULL)
		return (mode);
	token = last_control_operator->content;
	if (token->type & T_PIPE)
		mode |= P_OUTPUT;
	return (mode);
}

static int	redirect_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("redirect_fd():dup2()");
		return (1);
	}
	if (close(oldfd) == -1)
		perror("redirect_fd():close()");
	return (0);
}

static int	apply_pipe_redirections(t_pipe *pipeline)
{
	if (pipeline->mode == P_NONE)
		return (0);
	if (pipeline->mode & P_INPUT)
	{
		if (redirect_fd(pipeline->prev_fd_in, STDIN_FILENO))
		{
			close(pipeline->prev_fd_in);
			return (1);
		}
	}
	if (pipeline->mode & P_OUTPUT)
	{
		if (close(pipeline->fd[0]) == -1)
			perror("apply_pipe_redirections():close()");
		if (redirect_fd(pipeline->fd[1], STDOUT_FILENO))
		{
			close(pipeline->fd[1]);
			return (2);
		}
	}
	return (0);
}


//TODO: do quotes removal for the word
static int	do_heredoc(t_token *word)
{
	(void)word;
	return (-1);
}

static int	open_infile(t_token *redirect, t_token *word)
{
	int	fd;

	if (redirect->type & T_REDIRECT_INPUT)
	{
		parse_token(word);
		fd = open(word->data, O_RDONLY);
		if (fd == -1)
		{
			perror(word->data);
			return (1);
		}
	}
	else if (redirect->type & T_REDIRECT_HERE_DOC)
		fd = do_heredoc(word);
	else
		return (0);
	if (fd != -1 && redirect_fd(fd, STDIN_FILENO))
		close(fd);
	return (0);
}

static int	open_outfile(t_token *redirect, t_token *word)
{
	int				fd;
	int				flags;
	mode_t const	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	flags = O_CREAT | O_WRONLY;
	if (redirect->type & T_REDIRECT_OUTPUT)
		flags |= O_TRUNC;
	else if (redirect->type & T_REDIRECT_APPEND)
		flags |= O_APPEND;
	else
		return (0);
	parse_token(word);
	fd = open(word->data, flags, mode);
	if (fd == -1)
	{
		perror(word->data);
		return (1);
	}
	if (redirect_fd(fd, STDOUT_FILENO))
		close(fd);
	return (0);
}

static void	redirect_to_file(t_list *tokens)
{
	t_token	*token_redirect;
	t_token	*token_word;

	token_redirect = tokens->content;
	token_word = tokens->next->content;
	open_outfile(token_redirect, token_word);
	open_infile(token_redirect, token_word);
}

static void	apply_redirections(t_list *tokens, t_list *last)
{
	t_token	*token;

	while (tokens != last)
	{
		token = tokens->content;
		if (token->type & T_REDIRECT_OPERATOR)
		{
			redirect_to_file(tokens);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
}

typedef struct s_process
{
	pid_t	pid;
	int		exit_status;
}	t_process;

int	exec_prog(char **argv, char **envp);
void	free_token(void *content);

static t_process create_process(t_list *tokens, t_list *current,
		t_pipe *pipeline, char **argv, t_list *last)
{
	t_process	process;
	int			exit_status;

	process.pid = fork();
	if (process.pid == -1)
	{
		perror("create_process():fork()");
		if (pipeline->mode & P_INPUT)
			close(pipeline->fd[0]);
		close(pipeline->fd[1]);
		process.exit_status = 1;
		return (process);
	}
	if (process.pid == 0)
	{
		apply_pipe_redirections(pipeline);
		apply_redirections(current, last);
		exit_status = exec_prog(argv, NULL);
		ft_lstclear(&tokens, &free_token);
		free(argv);
		exit(exit_status);
	}
		
	process.exit_status = 0;
	return (process);
}

static t_process	execute_simple_cmd(t_list *tokens, t_list *current, t_pipe pipeline, t_list *control_operator)
{
	t_list		*args;
	char		**argv;
	t_process	proc;

	proc.pid = -1;
	proc.exit_status = 0;
	args = find_args(current, control_operator);
	if (args == NULL)
		return (proc);
	argv = list_to_tabstr(args);
	ft_lstclear(&args, &dummy);
	if (argv == NULL)
		return (proc);
	if (!is_a_builtin(argv[0]) || pipeline.mode != P_NONE)
		proc = create_process(tokens, current, &pipeline, argv, control_operator);
	free(argv);
	return (proc);
}

int	execute_line(t_list *tokens)
{
	t_list		*current;
	t_list		*control_operator;
	t_pipe		pipeline;
	t_process	proc;

	current = tokens;
	while (current != NULL)
	{
		control_operator = get_control_operator(current->next);
		pipeline.mode = get_pipe_mode(current, control_operator);
		if (pipeline.mode & P_OUTPUT)
		{
			if (pipe(pipeline.fd) == -1)
			{
				perror("execute_line():pipe()");
				return (EXIT_FAILURE);
			}
		}
		proc = execute_simple_cmd(tokens, current, pipeline, control_operator);
		if (pipeline.mode & P_INPUT)
		{
			if (close(pipeline.prev_fd_in) == -1)
				perror("execute_line():close()");
		}
		if (pipeline.mode & P_OUTPUT)
		{
			if (close(pipeline.fd[1]) == -1)
				perror("execute_line():close()");
			pipeline.prev_fd_in = pipeline.fd[0];
		}
		current = control_operator;
	}
	return (0);
}
