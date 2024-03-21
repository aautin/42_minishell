/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:35:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 20:16:05 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "parser.h"

int	open_infile(t_token *redirect, t_token *word);
int	open_outfile(t_token *redirect, t_token *word);

#endif
