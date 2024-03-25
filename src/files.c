/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:31:25 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 19:50:03 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

#include "libft/libft.h"

#include "parser.h"

int	open_infile(t_token *redirect, t_token *word, t_list **current_here_doc)
{
	int		fd;
	char	*filename;

	if (redirect->type & T_REDIRECT_INPUT)
	{
		parse_token(word);
		fd = open(word->data, O_RDONLY);
		if (fd == -1)
			perror(word->data);
	}
	else if (redirect->type & T_REDIRECT_HERE_DOC)
	{
		filename = (*current_here_doc)->content;
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			perror(filename);
		*current_here_doc = (*current_here_doc)->next;
	}
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
