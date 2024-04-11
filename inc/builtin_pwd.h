/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:38:37 by aautin            #+#    #+#             */
/*   Updated: 2024/04/11 15:28:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_PWD_H
# define BUILTIN_PWD_H

# include <unistd.h>
# include <stdio.h>
# include <linux/limits.h>

int	builtin_pwd(void);

#endif