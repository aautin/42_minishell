/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/20 15:42:39 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/libft.h"

#include "parser.h"

int	tokenize(t_list **tokens, char line[]);

void	free_tokens(void *content)
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

int	main(void)
{
	char	*line;
	t_list	*tokens;
	t_list	*bad_node;

	tokens = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		if (!tokenize(&tokens, line))
			printf("LINE : %s\n", line);
		free(line);
		bad_node = verify_tokens(tokens);
		if (bad_node != NULL)
			printf("Unexpected token '%s'\n", (char *)((t_token *)bad_node->content)->data);
		ft_lstiter(tokens, &print_token);
		ft_lstclear(&tokens, &free_tokens);
		tokens = NULL;
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
