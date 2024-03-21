/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:12:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 18:20:11 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"

char	*ask_input(char const prompt[])
{
	char	*line;
	char	*line_with_nl;

	if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
	{
		line = get_next_line(STDIN_FILENO);
		*ft_strrchr(line, '\n') = '\0';
	}
	return (line);
}

void	free_token(void *content)
{
	t_token *const	token = content;

	free(token->data);
	token->data = NULL;
	free(token);
}
