/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:41:33 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/27 18:36:24 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "here_doc_utils.h"
#include "minishell.h"
#include "parser.h"
#include "redirections.h"
#include "utils.h"

#define HERE_DOC_WARNING "warning: here_document delimited by end-of-file"

static char	*do_heredoc(t_token *word, int last_exit_status);
static int	read_heredoc(int fd, char const delim[], int last_exit_status, int delim_quoted);
static int	parse_line_heredoc(int fd, char const line[], int last_exit_status, int delim_quoted);

int	retrieve_heredoc(t_minishell *ms)
{
	t_token	*token;
	t_list	*tokens;
	char	*filename;

	tokens = ms->tokens;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type & T_REDIRECT_HERE_DOC)
		{
			filename = do_heredoc(tokens->next->content, ms->last_exit_status);
			if (filename == NULL || add_to_list(&ms->head_here_doc, filename))
			{
				ft_lstclear(&ms->head_here_doc, &free_here_doc);
				return (1);
			}
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (0);
}

static char	*do_heredoc(t_token *word, int last_exit_status)
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
	if (read_heredoc(fd, word->data, last_exit_status, word->type & T_QUOTED))
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

static int	read_heredoc(int fd, char const delim[], int last_exit_status, int delim_quoted)
{
	char			*line;
	int				std_fd[3];
	size_t const	size_delim = ft_strlen(delim) + 1;

	while (1)
	{
		line = ask_input("> ");
		if (line == NULL
			|| ft_strncmp(line, delim, size_delim) == 0
			|| parse_line_heredoc(fd, line, last_exit_status, delim_quoted))
			break ;
		free(line);
	}
	free(line);
	if (line != NULL)
		return (0);
	if (save_std_fd(std_fd))
		return (0);
	if (!redirect_fd(STDERR_FILENO, STDOUT_FILENO))
		printf(HERE_DOC_WARNING " (wanted '%s')\n", delim);
	if (reset_std_fd(std_fd))
		return (1);
	return (0);
}

static int	parse_line_heredoc(int fd, char const line[], int last_exit_status, int delim_quoted)
{
	t_token	token;
   
	token.data = ft_strdup(line);
	token.type = T_WORD;

	if (!delim_quoted)
	{
		if (expansion(&token, 1, last_exit_status))
		{
			free(token.data);
			return (1);
		}
	}
	ft_putendl_fd(token.data, fd);
	free(token.data);
	return (0);
}
