/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:04:19 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/24 18:37:34 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "minishell.h"

int		prepare_cmd(t_minishell *ms, char **argv);

#endif
