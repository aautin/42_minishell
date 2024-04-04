/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:55:46 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 14:30:31 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "libft/libft.h"

enum e_pipe_mode
{
	P_NONE = 0u,
	P_INPUT = (1u << 0),
	P_OUTPUT = (1u << 1)
};

typedef struct s_pipe
{
	int					fd[2];
	int					prev_fd_in;
	enum e_pipe_mode	mode;
}	t_pipe;

enum e_pipe_mode	get_pipe_mode(t_list *first_token, t_list *last_token);
void				close_pipes(t_pipe *pipeline);
int					redirect_pipes(t_pipe *pipeline);

#endif
