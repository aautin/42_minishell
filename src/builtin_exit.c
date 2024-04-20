/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:56:31 by aautin            #+#    #+#             */
/*   Updated: 2024/04/20 18:47:03 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "list_utils.h"
#include "minishell.h"

#define	TOO_MANY_ARGS "exit: too many arguments\n"
#define	NOT_DIGIT_ARG "exit: numeric argument required\n"

static int	is_number(char str[])
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
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

int	builtin_exit(char **argv, t_minishell *ms, int is_child, int const fd[3])
{
	unsigned char	exit_status;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		if (write(2, TOO_MANY_ARGS, ft_strlen(TOO_MANY_ARGS)) == -1)
			return (perror("builtin_exit():write()"), 1);
		return (2);
	}
	if (argv[1] == NULL)
		exit_status = ms->last_exit_status;
	else
	{
		if (!is_number(argv[1]))
			exit_status = ft_atoi(argv[1]);
		else
		{
			if (write(2, NOT_DIGIT_ARG, ft_strlen(NOT_DIGIT_ARG)) == -1)
				perror("builtin_exit():write()");
			exit_status = 2;
		}
	}
	clear_minishell(ms, is_child, fd);
	exit(exit_status);
}
