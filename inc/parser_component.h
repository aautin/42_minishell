/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_component.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:30:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/31 14:06:39 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_COMPONENT_H
# define PARSER_COMPONENT_H

# include "libft/libft.h"

# include "parser.h"

typedef struct s_expansion
{
	t_list			*envp;
	unsigned char	exit_status;
	int				ignore_quotes;
}	t_expansion;

t_list	*get_token_components(char data[]);
int		parse_components(t_expansion const *config, t_list *components);
int		components_to_data(t_token *token, t_list *components);

#endif