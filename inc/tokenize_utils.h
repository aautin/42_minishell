/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:44:13 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 20:26:34 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_UTILS_H
# define TOKENIZE_UTILS_H

# include "libft/libft.h"

# include "parser.h"

# define REDIRECT_OPERATOR "<>"
# define CONTROL_OPERATOR "|"
# define OPERATOR_TOKENS "<>|"
# define QUOTE_CHARS "\"'"

typedef enum e_action
{
	A_NONE = 0,
	A_CONTINUE,
	A_BREAK,
	A_RETURN
}	t_action;

typedef struct s_line_part
{
	char const	*line;
	int			index;
	int			mode;
	t_token		*token;
}	t_line_part;

void		store_and_create_token(t_list **tokens, t_line_part *line_part);
t_action	append_redirect_operator(t_line_part *line_part);
t_action	new_operator(t_list **tokens, t_line_part *line_part);
t_action	ignore_blank(t_list **tokens, t_line_part *line_part);

#endif
