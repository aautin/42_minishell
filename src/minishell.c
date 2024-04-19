/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:00:28 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/19 15:02:25 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

#include "libft/libft.h"

char	*ask_input(char const prompt[])
{
	char	*line;
	char	*newline;

	if (isatty(STDIN_FILENO))
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
