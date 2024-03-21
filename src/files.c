/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:31:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 18:14:43 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"
#include "pipeline.h"
#include "redirections.h"
#include "utils.h"

static int	do_heredoc(t_token *word);
static int	read_heredoc(int pipefd_write_end, t_token *word);
static int	parse_line_heredoc(char const line[], t_token *word, int fd);

int	open_infile(t_token *redirect, t_token *word)
{
	int	fd;

	if (redirect->type & T_REDIRECT_INPUT)
	{
		parse_token(word);
		fd = open(word->data, O_RDONLY);
		if (fd == -1)
			perror(word->data);
	}
	else if (redirect->type & T_REDIRECT_HERE_DOC)
		fd = do_heredoc(word);
	else
		return (-2);
	return (fd);
}

int	open_outfile(t_token *redirect, t_token *word)
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
		return (-2);
	parse_token(word);
	fd = open(word->data, flags, mode);
	if (fd == -1)
		perror(word->data);
	return (fd);
}

static int	do_heredoc(t_token *word)
{
	int	pipefd[2];
	int	status;

	unquote(word->data);
	if (pipe(pipefd) == -1)
	{
		perror("do_heredoc():pipe()");
		return (-1);
	}
	status = read_heredoc(pipefd[1], word);
	if (close(pipefd[1]) == -1)
		perror("do_heredoc():close()");
	if (status)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}

static int	read_heredoc(int pipefd_write_end, t_token *word)
{
	char			*line;
	int				std_fd[3];
	char *const		delim = word->data;
	size_t const	len_delim = ft_strlen(delim);

	while (1)
	{
		line = ask_input("> ");
		if (line == NULL
			|| (ft_strncmp(line, delim, len_delim) == 0
				&& line[len_delim] == '\n')
			|| parse_line_heredoc(line, word, pipefd_write_end))
			break ;
		free(line);
	}
	free(line);
	if (line != NULL)
		return (0);
	if (save_std_fd(std_fd))
		return (0);
	if (!redirect_fd(STDERR_FILENO, STDOUT_FILENO))
		printf("warning: here_document delimited by end-of-file (wanted '%s')\n", delim);
	if (reset_std_fd(std_fd))
		return (1);
	return (0);
}

static int	parse_line_heredoc(char const line[], t_token *word, int fd)
{
	t_list	*tokens;
	t_list	*current;
	t_token	*token;

	tokens = NULL;
	tokenize(&tokens, line);
	current = tokens;
	while (current != NULL)
	{
		token = current->content;
		if (token->type & T_WORD && !(word->type & T_QUOTED))
		{
			if (expansion(token))
				return (1);
		}
		ft_putstr_fd(token->data, fd);
		current = current->next;
	}
	ft_lstclear(&tokens, &free_token);
	ft_putchar_fd('\n', fd);
	return (0);
}
