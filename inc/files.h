/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:35:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/17 21:01:45 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "libft/libft.h"

# include "minishell.h"
# include "parser.h"

int		open_infile(t_minishell *ms, t_list **heredoc,
			t_token *redirect, t_token *word);
int		open_outfile(t_minishell *ms, t_token *redirect, t_token *word);
void	close_files(int fd1, int fd2);

#endif
