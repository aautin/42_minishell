/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 15:26:58 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

#include "files.h"
#include "parser.h"
#include "redirections.h"

static int	redirect_to_file(t_list *tokens);

int	redirect_fd(int oldfd, int newfd)
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
		close(std_fd[0]);
		perror("save_std_fd():dup(std_fd[1])");
		return (1);
	}
	std_fd[2] = dup(STDERR_FILENO);
	if (std_fd[2] == -1)
	{
		close(std_fd[0]);
		close(std_fd[1]);
		perror("save_std_fd():dup(std_fd[2])");
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

int	apply_normal_redirections(t_list *current, t_list *last)
{
	t_token	*token;

	while (current != last)
	{
		token = current->content;
		if (token->type & T_REDIRECT_OPERATOR)
		{
			if (redirect_to_file(current))
				return (1);
			current = current->next;
		}
		current = current->next;
	}
	return (0);
}

static int	redirect_to_file(t_list *operator)
{
	t_token	*redirect;
	t_token	*word;
	int		fd_in;
	int		fd_out;

	redirect = operator->content;
	word = operator->next->content;
	fd_in = open_infile(redirect, word);
	if (fd_in == -1)
		return (1);
	fd_out = open_outfile(redirect, word);
	if (fd_out == -1)
		return (1);
	if (fd_in != -2 && redirect_fd(fd_in, STDIN_FILENO))
	{
		close(fd_in);
		return (1);
	}
	if (fd_out != -2 && redirect_fd(fd_out, STDOUT_FILENO))
	{
		close(fd_out);
		return (1);
	}
	return (0);
}
