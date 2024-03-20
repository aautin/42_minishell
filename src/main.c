/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 20:14:18 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"
#include "utils.h"

void	free_token(void *content)
{
	free(((t_token *)content)->data);
	free(content);
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

int	execute_line(t_list *tokens, char **envp);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_list	*tokens;
	t_list	*bad_node;

	while (1)
	{
		tokens = NULL;
		line = ask_input("minishell> ");
		if (line == NULL)
			break ;
		*ft_strrchr(line, '\n') = '\0';
		if (*line != '\0')
			add_history(line);
		if (tokenize(&tokens, line) || tokens == NULL)
		{
			free(line);
			ft_lstclear(&tokens, &free_token);
			continue ;
		}
		free(line);
		bad_node = verify_tokens(tokens);
		if (bad_node == NULL)
			execute_line(tokens, envp);
		else
			printf("Unexpected token '%s'\n", (char *)((t_token *)bad_node->content)->data);
		ft_lstclear(&tokens, &free_token);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
