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

typedef struct s_expansion
{
	t_list			*envp;
	unsigned char	exit_status;
	int				ignore_quotes;
}	t_expansion;

int		nbr_len(unsigned char nbr);
void	nbr_data(char **data, unsigned char nbr);
int		change_quote_mode(char data, int *mode);
int		pathname_len(char *pathname);
int		expand_len(t_expansion const *config, char data[]);
void	expand_data(t_expansion const *config, char data[], char newdata[]);

#endif