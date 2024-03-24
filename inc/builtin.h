/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:43:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/24 18:42:18 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft/libft.h"

# include "minishell.h"

int	execute_builtin(char **argv, t_minishell *ms);
int	is_a_builtin(char const cmd[]);

#endif
