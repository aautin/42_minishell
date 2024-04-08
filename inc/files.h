/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:35:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/08 19:21:48 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "libft/libft.h"

# include "parser.h"

int		open_infile(t_token *redirect, t_token *word,
			t_list **current_heredoc, int last_exit_status);
int		open_outfile(t_token *redirect, t_token *word, int last_exit_status);
void	close_files(int fd1, int fd2);

#endif
