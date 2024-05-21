/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:33 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/17 21:03:39 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include "libft/libft.h"

# include "minishell.h"
# include "pipeline.h"

typedef struct s_process
{
	pid_t	pid;
	int		exit_status;
}	t_process;

typedef struct s_cmd
{
	t_list		*first_token;
	t_list		*last_token;
	t_pipe		pipeline;
	t_process	proc;
}	t_cmd;

int		find_args(t_list **args, t_minishell *ms,
			t_list *current_token, t_list *last_token);
t_list	*get_control_operator(t_list *current_token);
char	**listtoken_to_tabstr(t_list *args);
void	goto_next_heredoc(t_minishell *ms,
			t_list *current_token, t_list *last_token);

#endif
