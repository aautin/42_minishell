/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:30:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/25 14:50:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

int		nbr_len(unsigned char nbr);
void	nbr_data(char **data, unsigned char nbr, int nbr_len);
int		change_quote_mode(char data, int *mode);
int		pathname_len(char *pathname);
int		expand_len(char data[], int quote, unsigned char exit);
void	expand_data(char data[], char newdata[], int quote, unsigned char exit);

#endif