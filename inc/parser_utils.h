/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:30:29 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/29 18:50:35 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

typedef struct s_expansion
{
	t_list			*envp;
	unsigned char	exit_status;
	int				ignore_quotes;
	t_list			*components;
}	t_expansion;

size_t	nbr_len(unsigned char nbr);
void	nbr_data(char **data, unsigned char nbr);
int		change_quote_mode(char data, int *mode);
size_t	pathname_len(char *pathname);
size_t	expand_len(t_expansion const *config, char data[]);
void	expand_data(t_expansion const *config, char data[], char newdata[]);

#endif