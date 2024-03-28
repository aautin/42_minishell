/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:19:50 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/28 16:30:04 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

typedef struct s_minishell
{
	t_list	*tokens;
	t_list	*envl;
	t_list	*head_here_doc;
	t_list	*current_here_doc;
	int		last_exit_status;
}	t_minishell;

extern int	g_sig;

#endif
