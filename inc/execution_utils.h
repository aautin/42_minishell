/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:33 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 20:37:55 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include "libft/libft.h"

# include "pipeline.h"

typedef struct s_process
{
	pid_t	pid;
	int		exit_status;
}	t_process;

typedef struct s_simple_cmd
{
	t_list		*first;
	t_list		*last;
	t_pipe		pipeline;
	t_process	proc;
}	t_simple_cmd;

int		find_args(t_list *current, t_list *last, t_list **args);
t_list	*get_control_operator(t_list *current);
char	**listtoken_to_tabstr(t_list *current);

#endif
