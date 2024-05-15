/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:56:31 by aautin            #+#    #+#             */
/*   Updated: 2024/05/15 16:47:53 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "list_utils.h"
#include "minishell.h"

#define	TOO_MANY_ARGS "builtin_exit(): too many arguments\n"
#define	NOT_DIGIT_ARG "builtin_exit(): numeric argument required\n"

static int	is_number(char const str[])
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void clear_minishell(t_minishell *ms, int is_child, int const fd[3])
{
	if (is_child)
		ft_lstclear(&ms->head_heredoc, &free);
	else
		ft_lstclear(&ms->head_heredoc, &free_heredoc);
	
	ft_lstclear(&ms->tokens, &free_token);
	ft_lstclear(&ms->envl, &free);
	if (fd != NULL)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);	
	}
}

int	builtin_exit(char **argv, t_minishell *ms, int is_child, int const fd[3])
{
	int	exit_status;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		if (write(STDERR_FILENO, TOO_MANY_ARGS, ft_strlen(TOO_MANY_ARGS)) == -1)
			return (1);
		return (2);
	}
	if (argv[1] == NULL)
		exit_status = ms->last_exit_status;
	else if (is_number(argv[1]))
		exit_status = ft_atoi(argv[1]);
	else
	{
		write(STDERR_FILENO, NOT_DIGIT_ARG, ft_strlen(NOT_DIGIT_ARG));
		exit_status = 2;
	}
	clear_minishell(ms, is_child, fd);
	free(argv);
	if (ms->is_interactive)
	{
		rl_clear_history();
		write(STDOUT_FILENO, "exit\n", 5);
	}
	exit(exit_status);
}
