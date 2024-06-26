/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:30:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/31 18:10:37 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

# define NO_QUOTE 0
# define SG_QUOTE 1
# define DB_QUOTE 2

typedef enum e_token_type
{
	T_NONE = 0u,
	T_WORD = (1u << 0),
	T_QUOTED = (1u << 1),
	T_OPERATOR = (1u << 2),
	T_REDIRECT_OPERATOR = (1u << 3),
	T_CONTROL_OPERATOR = (1u << 4),
	T_REDIRECT_OUTPUT = (1u << 5),
	T_REDIRECT_INPUT = (1u << 6),
	T_REDIRECT_HEREDOC = (1u << 7),
	T_REDIRECT_APPEND = (1u << 8),
	T_PIPE = (1u << 9)
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}	t_token;

int		unquote(char data[], int starting_mode);
int		parse_token(t_token *token, t_list *envp, int exit_status,
			int ignore_quotes);
int		tokenize(t_list **tokens, char const line[]);
t_list	*verify_tokens(t_list *tokens);

#endif
