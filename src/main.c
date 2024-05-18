/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:01 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/05/18 20:35:25 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "libft/libft.h"

#include "builtin_echo.h"

int	main(void)
{
	char *const		line = readline("prompt>");
	char **const	split = ft_split(line, ' ');

	while (line)
	{
		builtin_echo(split);
		free(line);
		free(split);
		line = readline("prompt>");
	}
	return (EXIT_SUCCESS);
}
