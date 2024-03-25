/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:43:54 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/24 18:56:09 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft/libft.h"

# include "minishell.h"

int	execute_builtin(t_minishell *ms, char **argv);
int	is_a_builtin(char const cmd[]);

#endif