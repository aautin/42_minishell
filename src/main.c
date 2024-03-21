/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/21 16:15:33 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"

void	free_token(void *content)
{
	t_token	*const token = content;

	free(token->data);
	free(token);
}

void	print_token(void *content)
{
	if (((t_token *)content)->type & T_WORD)
	{
		printf("WORD ");
		if (((t_token *)content)->type & T_QUOTED)
			printf("QUOTED ");
		printf(": ");
	}
	else
	{
		if (((t_token *)content)->type == T_NONE)
			printf("NONE : ");
		if (((t_token *)content)->type & T_REDIRECT_OUTPUT)
			printf("REDIRECT_OUTPUT : ");
		if (((t_token *)content)->type & T_REDIRECT_INPUT)
			printf("REDIRECT_INPUT : ");
		if (((t_token *)content)->type & T_REDIRECT_HERE_DOC)
			printf("REDIRECT_HERE_DOC : ");
		if (((t_token *)content)->type & T_REDIRECT_APPEND)
			printf("REDIRECT_APPEND : ");
		if (((t_token *)content)->type & T_PIPE)
			printf("PIPE : ");
	}
	printf("%s\n", ((t_token *)content)->data);
}

int	main(void)
{
	int		status;
	char	*line;
	t_list	*tokens;
	t_list	*bad_node;

	while (1)
	{
		tokens = NULL;
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		status = tokenize(&tokens, line);
		free(line);
		if (!status)
		{
			bad_node = verify_tokens(tokens);
			if (bad_node != NULL)
				printf("Unexpected token '%s'\n", (char *)((t_token *)bad_node->content)->data);
			ft_lstiter(tokens, &print_token);
		}
		else if (status == 1)
			ft_putstr_fd("Error : quote not closed\n", STDERR_FILENO);
		ft_lstclear(&tokens, &free_token);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
