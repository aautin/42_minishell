/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:00:28 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/20 10:35:01 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

#include "libft/libft.h"

char	*ask_input(char const prompt[], int is_interactive)
{
	char	*line;
	char	*newline;

	if (is_interactive)
		line = readline(prompt);
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line != NULL)
		{
			newline = ft_strrchr(line, '\n');
			if (newline != NULL)
				*newline = '\0';
		}
	}
	return (line);
}
