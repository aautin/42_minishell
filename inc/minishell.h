/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:19:50 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/20 10:35:25 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

typedef struct s_minishell
{
	t_list	*tokens;
	t_list	*envl;
	t_list	*head_heredoc;
	t_list	*current_heredoc;
	int		last_exit_status;
	int		is_interactive;
}	t_minishell;

extern int	g_sig;

char	*ask_input(char const prompt[], int is_interactive);

#endif
