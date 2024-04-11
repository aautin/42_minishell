/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 15:25:05 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

#include "files.h"
#include "minishell.h"
#include "parser.h"
#include "redirections.h"

static int	open_file(t_minishell *ms, t_list *tokens, int fd[2]);

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
		perror("save_std_fd():dup(std_fd[1])");
		close(std_fd[0]);
		return (1);
	}
	std_fd[2] = dup(STDERR_FILENO);
	if (std_fd[2] == -1)
	{
		perror("save_std_fd():dup(std_fd[2])");
		close_files(std_fd[0], std_fd[1]);
		return (1);
	}
	return (0);
}

int	reset_std_fd(int std_fd[3])
{
	int	status;

	status = 0;
	if (redirect_fd(std_fd[2], STDERR_FILENO))
	{
		close(std_fd[2]);
		status = 1;
	}
	if (redirect_fd(std_fd[1], STDOUT_FILENO))
	{
		close(std_fd[1]);
		status = 1;
	}
	if (redirect_fd(std_fd[0], STDIN_FILENO))
	{
		close(std_fd[0]);
		status = 1;
	}
	return (status);
}

int	redirect_files(t_minishell *ms, t_list *current_token, t_list *last_token)
{
	int	fd[2];
	int	status;

	fd[0] = -1;
	fd[1] = -1;
	while (current_token != last_token)
	{
		if (((t_token *)current_token->content)->type & T_REDIRECT_OPERATOR)
		{
			if (open_file(ms, current_token, fd))
				return (1);
			current_token = current_token->next;
		}
		current_token = current_token->next;
	}
	status = 0;
	if (fd[0] >= 0)
		status += redirect_fd(fd[0], STDIN_FILENO);
	if (!status && fd[1] >= 0)
		status += redirect_fd(fd[1], STDOUT_FILENO);
	if (status)
		close_files(fd[0], fd[1]);
	return (status);
}

static int	open_file(t_minishell *ms, t_list *operator, int fd[2])
{
	t_token *const	redirect = operator->content;
	t_token *const	word = operator->next->content;
	int				fd_in;
	int				fd_out;

	fd_in = open_infile(ms, redirect, word);
	fd_out = open_outfile(ms, redirect, word);
	if (fd_in == -1 || fd_out == -1)
	{
		close_files(fd[0], fd[1]);
		return (1);
	}
	if (fd_in >= 0)
	{
		if (fd[0] >= 0 && close(fd[0]) == -1)
			perror("open_file():close(fd[0])");
		fd[0] = fd_in;
	}
	if (fd_out >= 0)
	{
		if (fd[1] >= 0 && close(fd[1]) == -1)
			perror("open_file():close(fd[1])");
		fd[1] = fd_out;
	}
	return (0);
}
