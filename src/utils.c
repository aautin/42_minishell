/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:12:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 19:14:23 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft/libft.h"

char	*ask_input(char const prompt[])
{
	char	*line;
	char	*line_with_nl;

	if (isatty(STDIN_FILENO))
	{
		line = readline(prompt);
		if (line == NULL)
			return (NULL);
		line_with_nl = ft_strjoin(line, "\n");
		if (line_with_nl == NULL)
			perror("ask_input():ft_strjoin()");
		free(line);
	}
	else
		line_with_nl = get_next_line(STDIN_FILENO);
	return (line_with_nl);
}
