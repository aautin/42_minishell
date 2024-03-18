/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_rules.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:49:57 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/18 15:58:15 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_RULES_H
# define TOKENIZE_RULES_H

# include "libft/libft.h"

# include "parser.h"
# include "tokenize_utils.h"

t_action	rule_1(t_list **tokens, t_line_part *line_part);
t_action	rule_2_3(t_list **tokens, t_line_part *line_part);
t_action	rule_4(t_line_part *line_part);
t_action	rule_6_7(t_list **tokens, t_line_part *line_part);
t_action	rule_8_9_10(t_line_part *line_part);

#endif
