/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 18:27:15 by pnguyen-         ###   ########.fr       */
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
