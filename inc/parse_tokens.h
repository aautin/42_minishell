/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:55:18 by aautin            #+#    #+#             */
/*   Updated: 2024/03/16 12:01:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TOKENS_H
# define PARSE_TOKENS_H

int	expansion(char *data, char *parsed_data, char *mode, unsigned int *parsed_i);
int	expansion_len(char *pathname, char *mode, unsigned int *i);
int	parse_tokens(t_list *tokens);

#endif