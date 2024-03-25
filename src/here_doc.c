/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:41:33 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 16:34:54 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "here_doc_utils.h"
#include "parser.h"
#include "redirections.h"
#include "utils.h"

#define HERE_DOC_WARNING "warning: here_document delimited by end-of-file"

static char	*do_heredoc(t_token *word);
static int	read_heredoc(int fd, char const delim[], int delim_quoted);
static int	parse_line_heredoc(int fd, char const line[], int delim_quoted);

int	retrieve_heredoc(t_list **here_docs, t_list *tokens)
{
	t_token	*token;
	char	*filename;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type & T_REDIRECT_HERE_DOC)
		{
			filename = do_heredoc(tokens->next->content);
			if (filename == NULL || add_to_list(here_docs, filename))
			{
				ft_lstclear(here_docs, &free_here_doc);
				return (1);
			}
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (0);
}

static char	*do_heredoc(t_token *word)
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
	if (read_heredoc(fd, word->data, word->type & T_QUOTED))
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

static int	read_heredoc(int fd, char const delim[], int delim_quoted)
{
	char			*line;
	int				std_fd[3];
	size_t const	size_delim = ft_strlen(delim) + 1;

	while (1)
	{
		line = ask_input("> ");
		if (line == NULL
			|| ft_strncmp(line, delim, size_delim) == 0
			|| parse_line_heredoc(fd, line, delim_quoted))
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

static int	parse_line_heredoc(int fd, char const line[], int delim_quoted)
{
	t_token	token;
   
	token.data = ft_strdup(line);
	token.type = T_WORD;

	if (!delim_quoted)
	{
		if (expansion(&token))
		{
			free(token.data);
			return (1);
		}
	}
	ft_putendl_fd(token.data, fd);
	free(token.data);
	return (0);
}
