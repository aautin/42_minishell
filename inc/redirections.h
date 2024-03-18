/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:26:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 20:29:55 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "libft/libft.h"

typedef enum e_pipe_mode
{
	P_NONE = 0u,
	P_INPUT = (1u << 0),
	P_OUTPUT = (1u << 1)
}	t_pipe_mode;

typedef struct s_pipe
{
	int			fd[2];
	int			prev_fd_in;
	t_pipe_mode	mode;
}	t_pipe;

t_pipe_mode	get_pipe_mode(t_list *first, t_list *last);
int			apply_pipe_redirections(t_pipe *pipeline);
void		apply_redirections(t_list *current, t_list *last);

#endif
