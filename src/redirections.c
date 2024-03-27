/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/27 18:42:03 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

#include "files.h"
#include "parser.h"
#include "redirections.h"

static int	redirect_to_file(t_list *tokens, t_list **current_here_doc, int last_exit_status, int fd[2]);

int	redirect_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("redirect_fd():dup2()");
		return (1);
	}
	if (oldfd != STDIN_FILENO
		&& oldfd != STDOUT_FILENO
		&& oldfd != STDERR_FILENO)
	{
		if (close(oldfd) == -1)
			perror("redirect_fd():close()");
	}
	return (0);
}

int	save_std_fd(int std_fd[3])
{
	std_fd[0] = dup(STDIN_FILENO);
	if (std_fd[0] == -1)
	{
		perror("save_std_fd():dup(std_fd[0])");
		return (1);
	}
	std_fd[1] = dup(STDOUT_FILENO);
	if (std_fd[1] == -1)
	{
		perror("save_std_fd():dup(std_fd[1])");
		close(std_fd[0]);
		return (1);
	}
	std_fd[2] = dup(STDERR_FILENO);
	if (std_fd[2] == -1)
	{
		perror("save_std_fd():dup(std_fd[2])");
		close(std_fd[0]);
		close(std_fd[1]);
		return (1);
	}
	return (0);
}

int	reset_std_fd(int std_fd[3])
{
	int	status;

	status = 0;
	if (redirect_fd(std_fd[0], STDIN_FILENO))
	{
		close(std_fd[0]);
		status = 1;
	}
	if (redirect_fd(std_fd[1], STDOUT_FILENO))
	{
		close(std_fd[1]);
		status = 1;
	}
	if (redirect_fd(std_fd[2], STDERR_FILENO))
	{
		close(std_fd[2]);
		status = 1;
	}
	return (status);
}

int	apply_normal_redirections(t_list *current_token, t_list *last_token,
		t_list **current_here_doc, int last_exit_status)
{
	int	fd[2];
	int	status;

	fd[0] = -1;
	fd[1] = -1;
	while (current_token != last_token)
	{
		if (((t_token *)current_token->content)->type & T_REDIRECT_OPERATOR)
		{
			if (redirect_to_file(current_token, current_here_doc, last_exit_status, fd))
			{
				close(fd[0]);
				close(fd[1]);
				return (1);
			}
			current_token = current_token->next;
		}
		current_token = current_token->next;
	}
	status = 0;
	if (fd[0] >= 0)
		status += redirect_fd(fd[0], STDIN_FILENO);
	if (fd[1] >= 0)
		status += redirect_fd(fd[1], STDOUT_FILENO);
	return (status);
}

static int	redirect_to_file(t_list *operator, t_list **current_here_doc, int last_exit_status, int fd[2])
{
	t_token *const	redirect = operator->content;
	t_token *const	word = operator->next->content;
	int				fd_in;
	int				fd_out;

	fd_in = open_infile(redirect, word, current_here_doc, last_exit_status);
	if (fd_in == -1)
		return (1);
	fd_out = open_outfile(redirect, word, last_exit_status);
	if (fd_out == -1)
		return (1);
	if (fd_in >= 0)
	{
		if (fd[0] >= 0 && close(fd[0]) == -1)
			perror("redirect_to_file():close(fd[0])");
		fd[0] = fd_in;
	}
	if (fd_out >= 0)
	{
		if (fd[1] >= 0 && close(fd[1]) == -1)
			perror("redirect_to_file():close(fd[1])");
		fd[1] = fd_out;
	}
	return (0);
}
