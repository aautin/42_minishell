/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:12:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/04/04 13:49:22 by pnguyen-         ###   ########.fr       */
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

	if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line != NULL)
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

void	my_perror(char const name[], char const msg[])
{
	char *const	full_msg = ft_strjoin(name, msg);

	if (full_msg == NULL)
	{
		perror("my_perror():ft_strjoin()");
		return ;
	}
	ft_putstr_fd(full_msg, STDERR_FILENO);
	free(full_msg);
}

int	add_to_list(t_list **list, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (node == NULL)
	{
		perror("add_to_list():ft_lstnew()");
		return (1);
	}
	ft_lstadd_back(list, node);
	return (0);
}

void	free_heredoc(void *content)
{
	char *const	filename = content;

	if (unlink(filename) == -1)
		perror(filename);
	free(filename);
}
