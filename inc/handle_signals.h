/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:03:22 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 19:56:37 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_SIGNALS_H
# define HANDLE_SIGNALS_H

typedef enum e_handler_sig
{
	H_DEFAULT = 0u,
	H_MINISHELL,
	H_HEREDOC,
	H_WAIT
}	t_handler_sig;

void	init_sigquit(t_handler_sig mode);
void	init_sigint(t_handler_sig mode);

#endif
