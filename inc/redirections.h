/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:26:15 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/11 15:06:54 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "libft/libft.h"

# include "minishell.h"

int	redirect_fd(int oldfd, int newfd);
int	save_std_fd(int std_fd[3]);
int	reset_std_fd(int std_fd[3]);
int	redirect_files(t_minishell *ms, t_list *first_token, t_list *last_token);

#endif
