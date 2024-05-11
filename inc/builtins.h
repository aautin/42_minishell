/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:44:03 by aautin            #+#    #+#             */
/*   Updated: 2024/05/11 20:30:38 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft/libft.h"

# include "minishell.h"

int	builtin_echo(char **argv);
int	builtin_env(t_list *envp);
int	builtin_exit(char **argv, t_minishell *ms, int is_child, int const fd[3]);
int	builtin_export(char **argv, t_list **envp);

#endif