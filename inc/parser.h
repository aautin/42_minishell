/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:30:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/11 17:03:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	T_NONE = 0u,
	T_WORD = (1u << 0),
	T_OPERATOR = (1u << 1),
	T_REDIRECT_OUTPUT = (1u << 2),
	T_REDIRECT_INPUT = (1u << 3),
	T_REDIRECT_HERE_DOC = (1u << 4),
	T_REDIRECT_APPEND = (1u << 5),
	T_PIPE = (1u << 6)
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}	t_token;

#endif