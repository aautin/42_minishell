/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:31:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 16:38:14 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "parser.h"

static int	do_heredoc(t_token *word);

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

//TODO: do quotes removal for the word
static int	do_heredoc(t_token *word)
{
	(void)word;
	return (-1);
}
