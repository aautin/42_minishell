/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:41:33 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/17 17:48:51 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "handle_signals.h"
#include "heredoc_utils.h"
#include "list_utils.h"
#include "minishell.h"
#include "parser.h"
#include "redirections.h"

#define HEREDOC_WARNING "warning: here_document delimited by end-of-file"

static int	process_heredoc(t_minishell *ms, t_token *token,
				t_list **last_node);
static char	*do_heredoc(t_minishell *ms, t_token *word);
static int	read_heredoc(t_minishell *ms, int fd,
				char const delim[], int delim_quoted);
static int	parse_line_heredoc(t_minishell *ms, int fd,
				char const line[], int delim_quoted);

int	retrieve_heredoc(t_minishell *ms)
{
	t_token	*token;
	t_list	*tokens;
	t_list	*last_node;
	int		status;

	tokens = ms->tokens;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type & T_REDIRECT_HEREDOC)
		{
			status = process_heredoc(ms, tokens->next->content, &last_node);
			if (status)
				return (status);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	process_heredoc(t_minishell *ms, t_token *token, t_list **last_node)
{
	char	*filename;
	int		std_fd[3];
	t_list	**last_heredoc;

	if (save_std_fd(std_fd))
		return (1);
	init_sigint(H_HEREDOC);
	filename = do_heredoc(ms, token);
	init_sigint(H_MINISHELL);
	if (reset_std_fd(std_fd))
	{
		free(filename);
		return (2);
	}
	if (ms->head_heredoc == NULL)
		last_heredoc = &ms->head_heredoc;
	else
		last_heredoc = last_node;
	if (filename == NULL || add_to_list(last_heredoc, filename))
		return (1);
	*last_node = ft_lstlast(*last_heredoc);
	return (0);
}

static char	*do_heredoc(t_minishell *ms, t_token *word)
{
	int		fd;
	char	*filename;

	unquote(word->data);
	filename = get_random_filename(word->data);
	if (filename == NULL)
		return (NULL);
	fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror(filename);
		free(filename);
		return (NULL);
	}
	if (read_heredoc(ms, fd, word->data, word->type & T_QUOTED))
	{
		close(fd);
		unlink(filename);
		free(filename);
		return (NULL);
	}
	if (close(fd) == -1)
		perror(filename);
	return (filename);
}

static int	read_heredoc(t_minishell *ms, int fd,
		char const delim[], int delim_quoted)
{
	char			*line;
	int				std_fd[3];
	size_t const	size_delim = ft_strlen(delim) + 1;

	while (1)
	{
		line = ask_input("> ", ms->is_interactive);
		if (line == NULL
			|| ft_strncmp(line, delim, size_delim) == 0
			|| parse_line_heredoc(ms, fd, line, delim_quoted))
			break ;
		free(line);
	}
	free(line);
	if (line != NULL)
		return (0);
	if (g_sig == SIGINT)
		return (1);
	if (save_std_fd(std_fd))
		return (0);
	if (!redirect_fd(STDERR_FILENO, STDOUT_FILENO))
		printf(HEREDOC_WARNING " (wanted '%s')\n", delim);
	if (reset_std_fd(std_fd))
		return (1);
	return (0);
}

static int	parse_line_heredoc(t_minishell *ms, int fd,
		char const line[], int delim_quoted)
{
	t_token	token;

	token.data = ft_strdup(line);
	if (token.data == NULL)
		return (1);
	token.type = T_WORD;
	if (!delim_quoted)
	{
		if (parse_token(&token, ms->envl, ms->last_exit_status, 1))
		{
			free(token.data);
			return (1);
		}
	}
	ft_putendl_fd(token.data, fd);
	free(token.data);
	return (0);
}
