/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:37:06 by aautin            #+#    #+#             */
/*   Updated: 2024/05/15 17:25:21 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft/libft.h"

# include "minishell.h"

int	builtin_cd(char **argv, t_list **envp);
int	builtin_echo(char **argv);
int	builtin_env(t_list *envp);
int	builtin_exit(char **argv, t_minishell *ms, int is_child, int const fd[3]);
int	builtin_export(char **argv, t_list **envp);
int	builtin_pwd(void);
int	builtin_unset(char **argv, t_list **envp);

#endif