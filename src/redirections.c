/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 20:48:17 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

#include "files.h"
#include "parser.h"
#include "redirections.h"

static int	redirect_fd(int oldfd, int newfd);
static void	redirect_to_file(t_list *tokens);

t_pipe_mode	get_pipe_mode(t_list *first, t_list *last)
{
	t_token		*token;
	t_pipe_mode	mode;

	mode = P_NONE;
	token = first->content;
	if (token->type & T_PIPE)
		mode |= P_INPUT;
	if (last == NULL)
		return (mode);
	token = last->content;
	if (token->type & T_PIPE)
		mode |= P_OUTPUT;
	return (mode);
}

int	apply_pipe_redirections(t_pipe *pipeline)
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

void	apply_redirections(t_list *current, t_list *last)
{
	t_token	*token;

	while (current != last)
	{
		token = current->content;
		if (token->type & T_REDIRECT_OPERATOR)
		{
			redirect_to_file(current);
			current = current->next;
		}
		current = current->next;
	}
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

static void	redirect_to_file(t_list *operator)
{
	t_token	*redirect;
	t_token	*word;
	int		fd_in;
	int		fd_out;

	redirect = operator->content;
	word = operator->next->content;
	fd_in = open_outfile(redirect, word);
	fd_out = open_infile(redirect, word);
	if (fd_in != -1)
	{
		if (redirect_fd(fd_in, STDIN_FILENO))
			close(fd_in);
	}
	if (fd_out != -1)
	{
		if (redirect_fd(fd_out, STDOUT_FILENO))
			close(fd_out);
	}
}
