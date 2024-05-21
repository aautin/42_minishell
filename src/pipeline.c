/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:53:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/21 17:28:23 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"
#include "pipeline.h"
#include "redirections.h"

enum e_pipe_mode	get_pipe_mode(t_list *first_token, t_list *last_token)
{
	t_token				*token;
	enum e_pipe_mode	mode;

	mode = P_NONE;
	token = first_token->content;
	if (token->type & T_PIPE)
		mode |= P_INPUT;
	if (last_token == NULL)
		return (mode);
	token = last_token->content;
	if (token->type & T_PIPE)
		mode |= P_OUTPUT;
	return (mode);
}

int	close_pipes(t_pipe *pipeline)
{
	if (pipeline->mode & P_INPUT)
	{
		if (close(pipeline->prev_fd_in) == -1)
		{
			perror("close_pipes():close()");
			return (1);
		}
	}
	if (pipeline->mode & P_OUTPUT)
	{
		if (close(pipeline->fd[1]) == -1)
		{
			perror("close_pipes():close()");
			return (1);
		}
		pipeline->prev_fd_in = pipeline->fd[0];
	}
	return (0);
}

int	redirect_pipes(t_pipe *pipeline)
{
	int	status;

	status = 0;
	if (pipeline->mode & P_INPUT)
	{
		if (redirect_fd(pipeline->prev_fd_in, STDIN_FILENO))
		{
			close(pipeline->prev_fd_in);
			status |= 2;
		}
	}
	if (pipeline->mode & P_OUTPUT)
	{
		if (close(pipeline->fd[0]) == -1)
		{
			perror("apply_pipe_redirections():close()");
			status |= 1;
		}
		if (redirect_fd(pipeline->fd[1], STDOUT_FILENO))
		{
			close(pipeline->fd[1]);
			status |= 2;
		}
	}
	return (status);
}
