/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:30:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/30 20:20:06 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "libft/libft.h"
# include "parser.h"

typedef struct s_expansion
{
	t_list			*envp;
	unsigned char	exit_status;
	int				ignore_quotes;
}	t_expansion;

size_t	pathname_len(char pathname[]);
int		parse_components(t_expansion const *config, t_list *components);
int		components_to_data(t_token *token, t_list *components);

#endif