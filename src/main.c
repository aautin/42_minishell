/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 18:50:07 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

int	execute_line(t_list *tokens);

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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*line;

	while (1)
	{
		line = ask_input("minishell> ");
		if (line == NULL)
			break ;
		*ft_strrchr(line, '\n') = '\0';
		if (*line != '\0')
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
