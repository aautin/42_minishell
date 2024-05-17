/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:31:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/17 21:00:31 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"

#include "minishell.h"
#include "parser.h"

int	open_infile(t_minishell *ms, t_list **heredoc,
		t_token *redirect, t_token *word)
{
	int		fd;
	char	*filename;

	if (redirect->type & T_REDIRECT_INPUT)
	{
		parse_token(word, ms->envl, ms->last_exit_status, 0);
		fd = open(word->data, O_RDONLY);
		if (fd == -1)
			perror(word->data);
	}
	else if (redirect->type & T_REDIRECT_HEREDOC)
	{
		filename = (*heredoc)->content;
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			perror(filename);
		(*heredoc) = (*heredoc)->next;
	}
	else
		return (-2);
	return (fd);
}

int	open_outfile(t_minishell *ms, t_token *redirect, t_token *word)
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
	parse_token(word, ms->envl, ms->last_exit_status, 0);
	fd = open(word->data, flags, mode);
	if (fd == -1)
		perror(word->data);
	return (fd);
}

void	close_files(int fd1, int fd2)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}
